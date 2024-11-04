USE jardineria;
-- pto1
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