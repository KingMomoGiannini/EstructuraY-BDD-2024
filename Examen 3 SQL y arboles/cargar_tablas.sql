CREATE Table pizza_types(
    pizza_type_id INT PRIMARY KEY AUTO_INCREMENT,
    nombre VARCHAR (20) NOT NULL,
    category VARCHAR (20) NOT NULL,
    ingredients VARCHAR (100) NOT NULL
);

CREATE TABLE customers(
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR (50) NOT NULL,
    last_name VARCHAR (50) NOT NULL,
    street_Address VARCHAR (100) NOT NULL,
    street_Number INT NOT NULL,
    City VARCHAR (50) NOT NULL,
    phone_Number VARCHAR (20) NOT NULL
);

CREATE TABLE subsidiaries(
    subsidiary_id INT PRIMARY KEY AUTO_INCREMENT,
    street_Adress VARCHAR (100) NOT NULL,
    street_Number INT NOT NULL,
    City VARCHAR (50) NOT NULL,
    phone_Number VARCHAR (20) NOT NULL,
    employees_number INT NOT NULL
);

CREATE TABLE orders(
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    order_date DATE NOT NULL,
    order_time TIME NOT NULL,
    customer_id INT NOT NULL,
    subsidiary_id INT NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
    FOREIGN KEY (subsidiary_id) REFERENCES subsidiaries(subsidiary_id)
);

CREATE TABLE pizzas(
    pizza_id INT PRIMARY KEY AUTO_INCREMENT,
    pizza_type_id INT NOT NULL,
    pizza_size VARCHAR (10) NOT NULL,
    price DECIMAL (5,2) NOT NULL,
    FOREIGN KEY (pizza_type_id) REFERENCES pizza_types(pizza_type_id)
);

CREATE TABLE order_details(
    order_detail_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    pizza_id INT NOT NULL,
    quantity INT NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (pizza_id) REFERENCES pizzas(pizza_id)
);

-- consigna: Realizar las consultas en SQL que permitan resolver las siguientes situaciones:
-- 1) Obtener los detalles de los pedidos hechos por un cliente llamado "John Doe", incluyendo el nombre de la pizza, cantidad, y la direccion de la sucursal donde realizo el pedido.
-- 2) Calcular los ingresos generados por cada sucursal en el mes de Octubre, considerando el precio de las pizzas y la cantidad pedida. Deberá mostrar el id de la sucursal, la dirección y el numero de esa dirección.
-- 3) Realizar un informe de las pizzas mas pedidas durante los fines de semana del mes actual, ordenando los resultados por cantidad.
-- 4) Mostrar los pedidos realizados por los clientes que viven en ciudades de Nueva York, Los Angeles y Chicago, y que su primer nombre empiece con A.
-- 5) Obtener los datos de los clientes, solo de aquellos que han pedido mas de 5 pizzas.
-- 6) Mostrar los tipos de pizzza que no han sido pedidos en los ultimos 30 dias.
-- Resolución:

-- pto1
SELECT  o.order_id,nombre, quantity, s.street_Adress, s.street_Number, s.City
FROM orders o
JOIN order_details od ON o.order_id = od.order_id
JOIN pizzas pz ON od.pizza_id = pz.pizza_id
JOIN pizza_types p ON pz.pizza_type_id = p.pizza_type_id
JOIN customers c ON o.customer_id = c.customer_id
JOIN subsidiaries s ON o.subsidiary_id = s.subsidiary_id
WHERE c.first_name = 'John' AND c.last_name = 'Doe';
--hecho por mí.
SELECT od.order_detail_id, c.first_name, c.last_name, pt.nombre, od.quantity, c.street_Address
FROM order_details od
JOIN pizzas p ON p.pizza_id = od.pizza_id
JOIN orders o ON o.order_id = od.order_id
JOIN pizza_types pt ON pt.pizza_type_id = p.pizza_type_id
JOIN subsidiaries s ON s.subsidiary_id = o.subsidiary_id
JOIN customers c ON c.customer_id = o.customer_id
WHERE c.first_name = 'John' AND c.last_name = 'Doe';

-- pto2
SELECT s.subsidiary_id, s.street_Adress, s.street_Number, SUM(p.price * od.quantity) as total
FROM orders o
JOIN order_details od ON o.order_id = od.order_id
JOIN pizzas p ON od.pizza_id = p.pizza_id
JOIN subsidiaries s ON o.subsidiary_id = s.subsidiary_id
WHERE MONTH(o.order_date) = 10
GROUP BY s.subsidiary_id;
-- pto 2 , condición de una fecha a otra
SELECT s.subsidiary_id, s.street_Adress, s.street_Number, SUM(p.price * od.quantity) as total
FROM orders o
JOIN order_details od ON o.order_id = od.order_id
JOIN pizzas p ON od.pizza_id = p.pizza_id
JOIN subsidiaries s ON o.subsidiary_id = s.subsidiary_id
WHERE o.order_date BETWEEN '2021-10-01' AND '2021-10-31'
GROUP BY s.subsidiary_id;
-- pto 2, esta vez traigo los datos desde la tabla de subsidiaries
SELECT s.subsidiary_id, s.street_Adress, s.street_Number, SUM(p.price * od.quantity) as total
FROM subsidiaries s
JOIN orders o ON o.subsidiary_id = s.subsidiary_id
JOIN order_details od ON o.order_id = od.order_id
JOIN pizzas p ON od.pizza_id = p.pizza_id
WHERE o.order_date BETWEEN '2021-10-01' AND '2021-10-31'
GROUP BY s.subsidiary_id;

-- pto3
SELECT pt.nombre, SUM(od.quantity) as total
FROM orders o
JOIN order_details od ON o.order_id = od.order_id
JOIN pizzas p ON od.pizza_id = p.pizza_id
JOIN pizza_types pt ON p.pizza_type_id = pt.pizza_type_id
WHERE DAYOFWEEK(o.order_date) = 1 OR DAYOFWEEK(o.order_date) = 7
GROUP BY pt.nombre
ORDER BY total DESC;

-- pto4
SELECT od.order_detail_id, c.first_name, c.City
from orders o
JOIN order_details od ON o.order_id = od.order_id
JOIN customers c ON c.customer_id = o.customer_id
WHERE c.City = 'New York' OR c.City = 'Los Angeles' OR c.City = 'Chicago' AND c.first_name LIKE 'A%';

-- pto5
SELECT c.first_name, c.last_name, SUM(od.quantity) as total
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
JOIN order_details od ON o.order_id = od.order_id
GROUP BY c.customer_id
HAVING total > 5;

-- pto6
SELECT pt.nombre
FROM pizza_types pt
JOIN pizzas p ON pt.pizza_type_id = p.pizza_type_id
JOIN order_details od ON p.pizza_id = od.pizza_id
JOIN orders o ON od.order_id = o.order_id
WHERE o.order_date < DATE_SUB(CURDATE(), INTERVAL 30 DAY)
GROUP BY pt.nombre
HAVING COUNT(od.order_detail_id) = 0;