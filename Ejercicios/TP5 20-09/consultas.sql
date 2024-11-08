-- Consultas  de selección
-- 1. Devuelve un listado con el código de oficina y la ciudad donde hay oficinas. 
-- 2. Devuelve un listado con la ciudad y el teléfono de las oficinas de España. 
-- 3. Devuelve un listado con el nombre, apellidos y email de los empleados cuyo jefe tiene un código de jefe igual a 7. 
-- 4. Devuelve el nombre del puesto, nombre, apellidos y email del jefe de la empresa. 
-- 5. Devuelve un listado con el nombre, apellidos y puesto de aquellos empleados que no sean representantes de ventas. 
-- 6. Devuelve un listado con el nombre de los todos los clientes españoles. 
-- 7. Devuelve un listado con los distintos estados por los que puede pasar un pedido. 
-- 8. Devuelve un listado con el codigo de cliente de aquellos clientes que realizaron algún pago en 2008. Tenga en cuenta que deberá eliminar aquellos códigos de cliente que aparezcan repetidos. Resuelva la consulta: 
-- Utilizando la función YEAR de MySQL. 
-- Utilizando la función DATE_FORMAT de MySQL. 
-- Sin utilizar ninguna de las funciones anteriores. 
-- 9. Devuelve un listado con el código de pedido, codigo de cliente, fecha esperada y fecha de entrega de los pedidos que no han sido entregados a tiempo. 
-- 10. Devuelve un listado con el código de pedido, codigo de cliente, fecha esperada y fecha de entrega de los pedidos cuya fecha de entrega ha sido al menos dos días antes de la fecha esperada. 
-- Utilizando la función ADDDATE de MySQL. 
-- Utilizando la función DATEDIFF de MySQL. 
-- 11. Devuelve un listado de todos los pedidos que fueron rechazados en 2009.
-- 12. Devuelve un listado de todos los pedidos que han sido entregados en el mes de enero de cualquier año. 
-- 13. Devuelve un listado con todos los pagos que se realizaron en el año 2008 mediante Paypal. Ordene el resultado de mayor a menor. 
-- 14. Devuelve un listado con todas las formas de pago que aparecen en la tabla pago. Tenga en cuenta que no deben aparecer formas de pago repetidas. 
-- 15. Devuelve un listado con todos los productos que pertenecen a la gama Ornamentales y que tienen más de 100 unidades en stock. El listado deberá estar ordenado por su precio de venta, mostrando en primer lugar los de mayor precio. 
-- 16. Devuelve un listado con todos los clientes que sean de la ciudad de Madrid y cuyo representante de ventas tenga el código de empleado 11 o 30. 

-- pto 1
SELECT codigo_oficina, ciudad 
FROM oficina;
-- pto2
SELECT ciudad, telefono 
FROM oficina 
WHERE pais = 'España';
-- pto3
SELECT nombre, apellido1, apellido2, email 
FROM empleado 
WHERE codigo_jefe = 7;
-- pto4
SELECT puesto, nombre, apellido1, empleado.apellido2, email, codigo_jefe 
FROM empleado 
WHERE empleado.puesto='Director General';
-- pto5
SELECT nombre, apellido1, apellido2, puesto 
FROM empleado 
WHERE puesto != 'Representante ventas';
-- pto6
SELECT nombre_cliente 
FROM cliente 
WHERE pais = 'spain';
-- pto7
SELECT DISTINCT estado 
FROM pedido;
-- pto8
SELECT DISTINCT codigo_cliente 
FROM pago 
WHERE YEAR(fecha_pago) = 2008;
SELECT DISTINCT codigo_cliente 
FROM pago 
WHERE DATE_FORMAT(fecha_pago, '%Y') = 2008;
SELECT DISTINCT codigo_cliente 
FROM pago 
WHERE fecha_pago BETWEEN '2008-01-01' AND '2008-12-31';
-- pto9
SELECT codigo_pedido, codigo_cliente, fecha_esperada, fecha_entrega 
FROM pedido 
WHERE fecha_entrega <= fecha_esperada;
-- pto10 
SELECT codigo_pedido, codigo_cliente, fecha_esperada, fecha_entrega, 
DATEDIFF(fecha_esperada, fecha_entrega) AS dias
FROM pedido 
WHERE DATEDIFF(fecha_esperada,fecha_entrega) BETWEEN 0 AND 2;
SELECT codigo_pedido, codigo_cliente, fecha_esperada, fecha_entrega,
ADDDATE(fecha_esperada, INTERVAL -2 DAY) AS fecha_referencia 
FROM pedido
WHERE fecha_entrega >= ADDDATE(fecha_esperada, INTERVAL -2 DAY) 
AND fecha_entrega <= fecha_esperada;
-- pto11
SELECT * FROM pedido 
WHERE estado = 'Rechazado' AND YEAR(fecha_entrega) = 2009;
-- pto12 
SELECT * FROM pedido 
WHERE MONTH(fecha_entrega) = 1;
-- pto13
SELECT * FROM pago 
WHERE YEAR(fecha_pago) = 2008 AND forma_pago = 'PayPal' 
ORDER BY codigo_cliente AND id_transaccion DESC;
-- pto14
SELECT DISTINCT forma_pago
FROM pago;
-- pto15
SELECT * FROM producto 
WHERE gama = 'Ornamentales' AND cantidad_en_stock > 100
ORDER BY precio_venta DESC;
-- pto16
SELECT * FROM cliente 
WHERE ciudad = 'Madrid' AND (codigo_empleado_rep_ventas = 11 OR codigo_empleado_rep_ventas = 30);
--------------------------- PARTE 2
-- Consultas  de resumen 
-- 1. ¿Cuántos empleados hay en la compañía? 
-- 2. ¿Cuántos clientes tiene cada país? 
-- 3. ¿Cuál fue el pago medio en 2009? 
-- 4. ¿Cuántos pedidos hay en cada estado? Ordena el resultado de forma 
-- descendente por el número de pedidos. 
-- 5. Calcula el precio de venta del producto más caro y más barato en una 
-- misma consulta. 
-- 6. Calcula el número de clientes que tiene la empresa. 
-- 7. ¿Cuántos clientes existen con domicilio en la ciudad de Madrid? 
-- 8. ¿Calcula cuántos clientes tiene cada una de las ciudades que empiezan 
-- por M? 
-- 9. Devuelve el nombre de los representantes de ventas y el número de 
-- clientes al que atiende cada uno. 
-- 10. Calcula el número de clientes que no tiene asignado representante de 
-- ventas.
-- 11. Calcula la fecha del primer y último pago realizado por cada uno de los 
-- clientes. El listado deberá mostrar el nombre y los apellidos de cada 
-- cliente. 
-- 12. Calcula el número de productos diferentes que hay en cada uno de los 
-- pedidos. 
-- 13. Calcula la suma de la cantidad total de todos los productos que aparecen 
-- en cada uno de los pedidos. 
-- 14. Devuelve un listado de los 20 productos más vendidos y el número total 
-- de unidades que se han vendido de cada uno. El listado deberá estar 
-- ordenado por el número total de unidades vendidas. 
-- 15. La facturación que ha tenido la empresa en toda la historia, indicando la 
-- base imponible, el IVA y el total facturado. La base imponible se calcula 
-- sumando el coste del producto por el número de unidades vendidas de 
-- la tabla detalle_pedido. El IVA es el 21 % de la base imponible, y el total la 
-- suma de los dos campos anteriores. 
-- 16. La misma información que en la pregunta anterior, pero agrupada por 
-- co ́digo de producto. 
-- 17. La misma información que en la pregunta anterior, pero agrupada por 
-- co ́digo de producto filtrada por los co ́digo que empiecen por OR. 
-- 18. Lista las ventas totales de los productos que hayan facturado más de 
-- 3000 euros. Se mostrará el nombre, unidades vendidas, total facturado y 
-- total facturado con impuestos (21% IVA). 
-- 19. Muestre la suma total de todos los pagos que se realizaron para cada 
-- uno de los años que aparecen en la tabla pagos.

-- Inicio de actividad: pto 1
SELECT COUNT(*) AS empleados FROM empleado;
-- pto2
SELECT pais, COUNT(*) AS clientes from cliente GROUP BY pais;
-- pto3
SELECT AVG(total) AS pago_medio 
FROM pago 
WHERE YEAR(fecha_pago) = 2009;
-- pto4
SELECT estado, COUNT(*) AS pedidos
FROM pedido
GROUP BY estado
ORDER BY pedidos DESC;
-- pto5
SELECT MAX(precio_venta) AS precio_maximo, MIN(precio_venta) AS precio_minimo
FROM producto;
-- pto6
SELECT COUNT(*) AS clientes
FROM cliente;
-- pto7
SELECT COUNT(*) AS clientes_madrid
FROM cliente 
WHERE ciudad = 'Madrid';
-- pto8
SELECT ciudad, COUNT(*) AS clientes
FROM cliente 
WHERE ciudad LIKE 'M%'
GROUP BY ciudad;
-- pto9
SELECT nombre, apellido1, apellido2, COUNT(*) AS clientes
FROM empleado
JOIN cliente ON empleado.codigo_empleado = cliente.codigo_empleado_rep_ventas
GROUP BY nombre, apellido1, apellido2;
-- pto10
SELECT COUNT(*) AS clientes_sin_representante
FROM cliente 
WHERE codigo_empleado_rep_ventas IS NULL;
-- pto11    
SELECT nombre_contacto, apellido_contacto, MIN(fecha_pago) AS primer_pago, MAX(fecha_pago) AS ultimo_pago
FROM cliente
JOIN pago ON cliente.codigo_cliente = pago.codigo_cliente
GROUP BY nombre_contacto, apellido_contacto;
-- pto12
SELECT codigo_pedido, COUNT(*) AS productos
FROM detalle_pedido
GROUP BY codigo_pedido;
-- pto13
SELECT codigo_pedido, SUM(cantidad) AS cantidad_total
FROM detalle_pedido
GROUP BY codigo_pedido;
-- pto14
SELECT codigo_producto, SUM(cantidad) AS unidades_vendidas
FROM detalle_pedido
GROUP BY codigo_producto
ORDER BY unidades_vendidas DESC
LIMIT 20;
-- pto15
SELECT SUM(precio_venta * cantidad) AS base_imponible,
SUM(precio_venta * cantidad) * 0.21 AS iva,
SUM(precio_venta * cantidad) + SUM(precio_venta * cantidad) * 0.21 AS total_facturado
FROM detalle_pedido;
-- pto16
SELECT codigo_producto, SUM(precio_venta * cantidad) AS base_imponible,
SUM(precio_venta * cantidad) * 0.21 AS iva,
SUM(precio_venta * cantidad) + SUM(precio_venta * cantidad) * 0.21 AS total_facturado
FROM detalle_pedido
GROUP BY codigo_producto;
-- pto17
SELECT codigo_producto, SUM(precio_venta * cantidad) AS base_imponible,
SUM(precio_venta * cantidad) * 0.21 AS iva,
SUM(precio_venta * cantidad) + SUM(precio_venta * cantidad) * 0.21 AS total_facturado
FROM detalle_pedido
WHERE codigo_producto LIKE 'OR%'
GROUP BY codigo_producto;
-- pto18
SELECT nombre, SUM(cantidad) AS unidades_vendidas,
SUM(precio_venta * cantidad) AS total_facturado,
SUM(precio_venta * cantidad) + SUM(precio_venta * cantidad) * 0.21 AS total_facturado_con_iva
FROM detalle_pedido
JOIN producto ON detalle_pedido.codigo_producto = producto.codigo_producto
GROUP BY nombre
HAVING total_facturado > 3000;
-- pto19
SELECT YEAR(fecha_pago) AS año, SUM(total) AS total_pagado
FROM pago
GROUP BY YEAR(fecha_pago);
-- Consultas multitabla (Composición interna) 
-- 1. Obtén un listado con el nombre de cada cliente y el nombre y apellido de 
-- su representante de ventas. 
-- 2. Muestra el nombre de los clientes que hayan realizado pagos junto con 
-- el nombre de sus representantes de ventas. 
-- 3. Muestra el nombre de los clientes que no hayan realizado pagos junto 
-- con el nombre de sus representantes de ventas. 
-- 4. Devuelve el nombre de los clientes que han hecho pagos y el nombre de 
-- sus representantes junto con la ciudad de la oficina a la que pertenece el 
-- representante. 
-- 5. Devuelve el nombre de los clientes que no hayan hecho pagos y el 
-- nombre de sus representantes junto con la ciudad de la oficina a la que 
-- pertenece el representante. 
-- 6. Lista la dirección de las oficinas que tengan clientes en Fuenlabrada. 
-- 7. Devuelve el nombre de los clientes y el nombre de sus representantes 
-- junto con la ciudad de la oficina a la que pertenece el representante. 
-- 8. Devuelve un listado con el nombre de los empleados junto con el 
-- nombre de sus jefes. 
-- 9. Devuelve un listado que muestre el nombre de cada empleado, el 
-- nombre de su jefe y el nombre del jefe de su jefe. 
-- 10. Devuelve el nombre de los clientes a los que no se les ha entregado a 
-- tiempo un pedido. 
-- 11. Devuelve un listado de las diferentes gamas de producto que ha 
-- comprado cada cliente.

-- pto1
SELECT nombre_cliente, nombre, apellido1, apellido2
FROM cliente
JOIN empleado ON cliente.codigo_empleado_rep_ventas = empleado.codigo_empleado;
-- pto2
SELECT nombre_cliente, nombre, apellido1, apellido2
FROM cliente
JOIN empleado ON cliente.codigo_empleado_rep_ventas = empleado.codigo_empleado
JOIN pago ON cliente.codigo_cliente = pago.codigo_cliente;
-- pto3 (composición interna)
SELECT nombre_cliente, nombre, apellido1, apellido2
FROM cliente
JOIN empleado ON cliente.codigo_empleado_rep_ventas = empleado.codigo_empleado
INNER JOIN pago ON cliente.codigo_cliente <> pago.codigo_cliente;
-- pto4
SELECT nombre_cliente, nombre, apellido1, apellido2, oficina.ciudad
FROM cliente
JOIN empleado ON cliente.codigo_empleado_rep_ventas = empleado.codigo_empleado
JOIN oficina ON empleado.codigo_oficina = oficina.codigo_oficina
JOIN pago ON cliente.codigo_cliente = pago.codigo_cliente;

-- pto5
SELECT nombre_cliente, nombre, apellido1, apellido2, oficina.ciudad
FROM cliente
JOIN empleado ON cliente.codigo_empleado_rep_ventas = empleado.codigo_empleado
JOIN oficina ON empleado.codigo_oficina = oficina.codigo_oficina
LEFT JOIN pago ON cliente.codigo_cliente = pago.codigo_cliente
WHERE pago.codigo_cliente IS NULL;
-- pto6
SELECT cliente.linea_direccion1, cliente.linea_direccion2, cliente.ciudad, cliente.pais
FROM oficina
JOIN empleado ON oficina.codigo_oficina = empleado.codigo_oficina
JOIN cliente ON empleado.codigo_empleado = cliente.codigo_empleado_rep_ventas
WHERE cliente.ciudad = 'Fuenlabrada';
-- pto7
SELECT nombre_cliente, nombre, apellido1, apellido2, oficina.ciudad
FROM cliente
JOIN empleado ON cliente.codigo_empleado_rep_ventas = empleado.codigo_empleado
JOIN oficina ON empleado.codigo_oficina = oficina.codigo_oficina;
-- pto8
SELECT empleado.nombre, empleado.apellido1, empleado.apellido2, jefe.nombre, jefe.apellido1, jefe.apellido2
FROM empleado
JOIN empleado jefe ON empleado.codigo_jefe = jefe.codigo_empleado;
-- pto9
SELECT empleado.nombre, empleado.apellido1, empleado.apellido2, jefe.nombre, jefe.apellido1, jefe.apellido2, jefe_jefe.nombre, jefe_jefe.apellido1, jefe_jefe.apellido2
FROM empleado
JOIN empleado jefe ON empleado.codigo_jefe = jefe.codigo_empleado
JOIN empleado jefe_jefe ON jefe.codigo_jefe = jefe_jefe.codigo_empleado;
-- pto10
SELECT nombre_cliente
FROM cliente
JOIN pedido ON cliente.codigo_cliente = pedido.codigo_cliente
WHERE pedido.fecha_entrega > pedido.fecha_esperada;
-- pto11
SELECT nombre_cliente, gama_producto.gama
FROM cliente
JOIN pedido ON cliente.codigo_cliente = pedido.codigo_cliente
JOIN detalle_pedido ON pedido.codigo_pedido = detalle_pedido.codigo_pedido
JOIN producto ON detalle_pedido.codigo_producto = producto.codigo_producto
JOIN gama_producto ON producto.gama = gama_producto.gama;
