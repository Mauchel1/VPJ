-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema vpj
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema vpj
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `vpj` DEFAULT CHARACTER SET utf8 ;
USE `vpj` ;

-- -----------------------------------------------------
-- Table `vpj`.`auftrag`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`auftrag` (
  `id_auftrag` INT NOT NULL,
  `status` INT NOT NULL,
  PRIMARY KEY (`id_auftrag`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`Produktionsprozess`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`Produktionsprozess` (
  `id_Produkt` INT NOT NULL,
  `station_1` INT NULL,
  `dauer_station_1` INT NULL,
  `station_2` INT NULL,
  `dauer_station_2` INT NULL,
  `station_3` INT NULL,
  `dauer_station_3` INT NULL,
  `station_4` INT NULL,
  `dauer_station_4` INT NULL,
  `station_5` INT NULL,
  `dauer_station_5` INT NULL,
  `station_6` INT NULL,
  `dauer_station_6` INT NULL,
  PRIMARY KEY (`id_Produkt`))
ENGINE = InnoDB
COMMENT = '					';


-- -----------------------------------------------------
-- Table `vpj`.`Werkstueck`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`Werkstueck` (
  `RFID_Werkstueck` INT UNSIGNED NOT NULL,
  `Fortschritt` INT NOT NULL,
  `Produktionsprozess_id_Produkt` INT NOT NULL,
  `auftrag_id_auftrag` INT NOT NULL,
  INDEX `fk_Werkstueck_Produktionsprozess1_idx` (`Produktionsprozess_id_Produkt` ASC) ,
  INDEX `fk_Werkstueck_auftrag1_idx` (`auftrag_id_auftrag` ASC) ,
  PRIMARY KEY (`RFID_Werkstueck`),
  CONSTRAINT `fk_Werkstueck_Produktionsprozess1`
    FOREIGN KEY (`Produktionsprozess_id_Produkt`)
    REFERENCES `vpj`.`Produktionsprozess` (`id_Produkt`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Werkstueck_auftrag1`
    FOREIGN KEY (`auftrag_id_auftrag`)
    REFERENCES `vpj`.`auftrag` (`id_auftrag`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`Roboter`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`Roboter` (
  `id_Roboter` INT NOT NULL,
  `Akkuleistung` INT NULL,
  `betriebsstatus` TINYINT NULL,
  `Werkstueck_RFID_Werkstueck` INT UNSIGNED NULL,
  PRIMARY KEY (`id_Roboter`),
  INDEX `fk_Roboter_Werkstueck1_idx` (`Werkstueck_RFID_Werkstueck` ASC) ,
  CONSTRAINT `fk_Roboter_Werkstueck1`
    FOREIGN KEY (`Werkstueck_RFID_Werkstueck`)
    REFERENCES `vpj`.`Werkstueck` (`RFID_Werkstueck`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`Arbeitsplatz`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`Arbeitsplatz` (
  `id_Arbeitsplatz` INT NOT NULL,
  `Status` TINYINT NOT NULL,
  `Roboter_id_Roboter` INT NULL,
  `Werkstueck_RFID_Werkstueck` INT UNSIGNED NULL,
  PRIMARY KEY (`id_Arbeitsplatz`),
  INDEX `fk_Station_Roboter1_idx` (`Roboter_id_Roboter` ASC) ,
  INDEX `fk_Arbeitsplatz_Werkstueck1_idx` (`Werkstueck_RFID_Werkstueck` ASC) ,
  CONSTRAINT `fk_Station_Roboter1`
    FOREIGN KEY (`Roboter_id_Roboter`)
    REFERENCES `vpj`.`Roboter` (`id_Roboter`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Arbeitsplatz_Werkstueck1`
    FOREIGN KEY (`Werkstueck_RFID_Werkstueck`)
    REFERENCES `vpj`.`Werkstueck` (`RFID_Werkstueck`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`RFID_Timestamp`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`RFID_Timestamp` (
  `id_Timestamp` INT NOT NULL,
  `Arbeitsplatz_id_Arbeitsplatz` INT NOT NULL,
  `Werkstueck_RFID_Werkstueck` INT UNSIGNED NOT NULL,
  `Zeitstempel` BIGINT NOT NULL,
  `Status` TINYINT NOT NULL,
  PRIMARY KEY (`id_Timestamp`),
  INDEX `fk_RFID-Timestamp_Station1_idx` (`Arbeitsplatz_id_Arbeitsplatz` ASC) ,
  INDEX `fk_RFID-Timestamp_Werkstueck1_idx` (`Werkstueck_RFID_Werkstueck` ASC) ,
  CONSTRAINT `fk_RFID-Timestamp_Station1`
    FOREIGN KEY (`Arbeitsplatz_id_Arbeitsplatz`)
    REFERENCES `vpj`.`Arbeitsplatz` (`id_Arbeitsplatz`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_RFID-Timestamp_Werkstueck1`
    FOREIGN KEY (`Werkstueck_RFID_Werkstueck`)
    REFERENCES `vpj`.`Werkstueck` (`RFID_Werkstueck`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`Parkplatz`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`Parkplatz` (
  `id_Parkplatz` INT NOT NULL,
  `Status` TINYINT NOT NULL,
  `Roboter_id_Roboter` INT NULL,
  PRIMARY KEY (`id_Parkplatz`),
  INDEX `fk_Parkplatz_Roboter1_idx` (`Roboter_id_Roboter` ASC) ,
  CONSTRAINT `fk_Parkplatz_Roboter1`
    FOREIGN KEY (`Roboter_id_Roboter`)
    REFERENCES `vpj`.`Roboter` (`id_Roboter`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`taggen`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`taggen` (
  `id_taggen` INT NOT NULL,
  `Werkstueck_RFID_Werkstueck` INT UNSIGNED NULL,
  PRIMARY KEY (`id_taggen`),
  INDEX `fk_taggen_Werkstueck1_idx` (`Werkstueck_RFID_Werkstueck` ASC) ,
  CONSTRAINT `fk_taggen_Werkstueck1`
    FOREIGN KEY (`Werkstueck_RFID_Werkstueck`)
    REFERENCES `vpj`.`Werkstueck` (`RFID_Werkstueck`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `vpj`.`Zeit`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `vpj`.`Zeit` (
  `id_Zeit` INT NOT NULL,
  `aktuelle_Zeit` DATETIME NULL,
  PRIMARY KEY (`id_Zeit`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
