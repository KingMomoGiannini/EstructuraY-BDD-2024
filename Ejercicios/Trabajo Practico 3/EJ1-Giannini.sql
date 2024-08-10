/*Crear esquema con la tabla 'libro' y sus atributos (hecho en MySQL Workbench):*/

-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema TP3EyBDD
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema TP3EyBDD
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `TP3EyBDD` DEFAULT CHARACTER SET utf8 ;
USE `TP3EyBDD` ;

-- -----------------------------------------------------
-- Table `TP3EyBDD`.`libro`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TP3EyBDD`.`libro` (
  `codigo` INT NOT NULL AUTO_INCREMENT,
  `titulo` VARCHAR(40) NOT NULL,
  `autor` VARCHAR(40) NULL,
  `editorial` VARCHAR(40) NULL,
  `precio` DECIMAL(5,2) NULL,
  `edicion` DATE NULL,
  PRIMARY KEY (`codigo`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

/* Consignas y Respuestas */


/*A) Agregar el campo "cantidad", de tipo int NOT NULL */
ALTER TABLE libro ADD cantidad INT NOT NULL;
/*b) Eliminar el campo "edición" */
ALTER TABLE libro DROP COLUMN edicion;
/*c) Modificar el tipo del campo "titulo" para poder almacenar una 
longitud de 30 caracteres y que no permita valores nulos*/
ALTER TABLE libro MODIFY COLUMN titulo VARCHAR(30) NOT NULL;
/*d) Agregar el campo ISBN de tipo carácter (20) e indexar el campo*/
ALTER TABLE libro ADD ISBN CHAR(20);
CREATE INDEX idx_ISBN ON libro(ISBN);