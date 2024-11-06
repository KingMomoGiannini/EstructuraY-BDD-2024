INSERT pizza_types (nombre, category, ingredients) VALUES ('Muzzarella', 'Clasica', 'Muzzarella, Tomate, Oregano');
INSERT pizza_types (nombre, category, ingredients) VALUES ('Napolitana', 'Clasica', 'Muzzarella, Tomate, Jamon, Aceitunas');
INSERT pizza_types (nombre, category, ingredients) VALUES ('Fugazzeta', 'Clasica', 'Muzzarella, Cebolla, Oregano');
INSERT pizza_types (nombre, category, ingredients) VALUES ('Calabresa', 'Especial', 'Muzzarella, Tomate, Calabresa, Aceitunas');
INSERT pizza_types (nombre, category, ingredients) VALUES ('4 Quesos', 'Especial', 'Muzzarella, Tomate, Roquefort, Parmesano, Gruyere');
-- Clientes
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('John', 'Doe', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Jane', 'Doe', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Homer', 'Simpson', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Marge', 'Simpson', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Bart', 'Simpson', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Lisa', 'Simpson', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
-- clientes cuyo primer nombre empieza con A
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Apu', 'Nahasapeemapetilon', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Abe', 'Simpson', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');
INSERT customers (first_name, last_name, street_Address, street_Number, City, phone_Number) VALUES ('Amanda', 'Hugandkiss', 'Av. Siempre Viva', 123, 'Springfield', '555-1234');


-- Sucursales, todas diferentes, de Nueva York, Los Angeles, Chicago, Miami, Houston, Dallas, con distintas direcciones y cantidades de empleados
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES ('Av. Siempre Viva', 123, 'Springfield', '555-1234', 10);
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES (' 123 Sesame St', 123, 'New York', '555-1234', 10);
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES ('calle Falsa 123', 123, 'Los Angeles', '555-1234', 10);
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES ('Av. Siempre Viva', 123, 'Chicago', '555-1234', 10);
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES ('Av. Siempre Viva', 123, 'Miami', '555-1234', 10);
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES ('Av. Siempre Viva', 123, 'Houston', '555-1234', 10);
INSERT subsidiaries (street_Adress, street_Number, City, phone_Number, employees_number) VALUES ('Av. Siempre Viva', 123, 'Dallas', '555-1234', 10);

-- Pedidos, con fechas de octubre, de clientes y sucursales de las ciudades mencionadas
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-01', '12:00:00', 1, 1);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-02', '12:00:00', 2, 2);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-03', '12:00:00', 3, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-04', '12:00:00', 4, 4);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-05', '12:00:00', 5, 5);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-06', '12:00:00', 6, 6);

-- Pizzas, de los tipos mencionados, con precios y tamaños
INSERT pizzas (pizza_type_id, pizza_size, price) VALUES (1, 'Grande', 500);
INSERT pizzas (pizza_type_id, pizza_size, price) VALUES (2, 'Grande', 600);
INSERT pizzas (pizza_type_id, pizza_size, price) VALUES (3, 'Grande', 700);
INSERT pizzas (pizza_type_id, pizza_size, price) VALUES (4, 'Grande', 800);
INSERT pizzas (pizza_type_id, pizza_size, price) VALUES (5, 'Grande', 900);

-- Detalles de pedidos, con cantidad de pizzas
INSERT order_details (order_id, pizza_id, quantity) VALUES (1, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (2, 2, 2);
INSERT order_details (order_id, pizza_id, quantity) VALUES (3, 3, 3);
INSERT order_details (order_id, pizza_id, quantity) VALUES (4, 4, 4);
INSERT order_details (order_id, pizza_id, quantity) VALUES (5, 5, 5);
INSERT order_details (order_id, pizza_id, quantity) VALUES (6, 1, 1);

-- pto 3 realizar los insert de los pedidos de los fines de semana
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-09', '12:00:00', 1, 1);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-09', '13:00:00', 2, 2);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-09', '14:00:00', 2, 2);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-10', '12:00:00', 2, 2);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-10', '13:00:00', 2, 2);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-16', '14:00:00', 3, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-17', '12:00:00', 4, 4);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-23', '13:00:00', 5, 5);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-24', '14:00:00', 6, 6);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-30', '12:00:00', 1, 1);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-31', '13:00:00', 2, 2);

-- insertar detalles de los pedidos anteriores
INSERT order_details (order_id, pizza_id, quantity) VALUES (7, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (8, 2, 2);
INSERT order_details (order_id, pizza_id, quantity) VALUES (9, 3, 3);
INSERT order_details (order_id, pizza_id, quantity) VALUES (10, 4, 4);
INSERT order_details (order_id, pizza_id, quantity) VALUES (11, 5, 5);
INSERT order_details (order_id, pizza_id, quantity) VALUES (12, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (13, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (14, 2, 2);
INSERT order_details (order_id, pizza_id, quantity) VALUES (15, 3, 3);
INSERT order_details (order_id, pizza_id, quantity) VALUES (16, 4, 4);
INSERT order_details (order_id, pizza_id, quantity) VALUES (17, 5, 5);

-- clientes cuyo primer nombre empieza con A, CAMBIAR DOMICILIOS A NUEVA YORK, CHICAGO Y LOS ANGELES
UPDATE customers SET City = 'New York' WHERE first_name = 'Apu';
UPDATE customers SET City = 'Chicago' WHERE first_name = 'Abe';
UPDATE customers SET City = 'Los Angeles' WHERE first_name = 'Amanda';

-- Pedidos realizados por los clientes recien mencionados
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-09', '12:00:00', 7, 2);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-09', '13:00:00', 8, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-09', '14:00:00', 8, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-10', '12:00:00', 8, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-10', '13:00:00', 8, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-16', '14:00:00', 8, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-16', '14:00:00', 8, 3);
INSERT orders (order_date, order_time, customer_id, subsidiary_id) VALUES ('2021-10-16', '14:00:00', 9, 4);

-- insertar detalles de los pedidos anteriores
INSERT order_details (order_id, pizza_id, quantity) VALUES (18, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (19, 2, 2);
INSERT order_details (order_id, pizza_id, quantity) VALUES (20, 3, 3);
INSERT order_details (order_id, pizza_id, quantity) VALUES (21, 4, 4);
INSERT order_details (order_id, pizza_id, quantity) VALUES (22, 5, 5);
INSERT order_details (order_id, pizza_id, quantity) VALUES (23, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (24, 1, 1);
INSERT order_details (order_id, pizza_id, quantity) VALUES (25, 2, 2);

