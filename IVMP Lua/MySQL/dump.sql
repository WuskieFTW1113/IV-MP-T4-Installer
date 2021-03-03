-- MySQL dump 10.13  Distrib 5.7.9, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: iv
-- ------------------------------------------------------
-- Server version	5.7.9-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `adm`
--

DROP TABLE IF EXISTS `adm`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `adm` (
  `fk` mediumint(9) NOT NULL,
  `level` tinyint(4) NOT NULL,
  `pnel` char(64) NOT NULL,
  PRIMARY KEY (`fk`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `apoints`
--

DROP TABLE IF EXISTS `apoints`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `apoints` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `x` float NOT NULL,
  `y` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=159 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `areas`
--

DROP TABLE IF EXISTS `areas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `areas` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `name` varchar(30) NOT NULL,
  `rb` tinyint(4) unsigned NOT NULL,
  `rt` tinyint(4) unsigned NOT NULL,
  `lb` tinyint(4) unsigned NOT NULL,
  `lt` tinyint(4) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=75 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `bans`
--

DROP TABLE IF EXISTS `bans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bans` (
  `id` smallint(6) unsigned NOT NULL AUTO_INCREMENT,
  `fk` mediumint(9) NOT NULL,
  `typ` tinyint(4) NOT NULL,
  `due` datetime DEFAULT NULL,
  `reason` varchar(40) NOT NULL,
  `staff` mediumint(9) NOT NULL,
  `ip` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fkban_idx` (`fk`),
  CONSTRAINT `fkban` FOREIGN KEY (`fk`) REFERENCES `players` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `biz`
--

DROP TABLE IF EXISTS `biz`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `biz` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `owner` mediumint(9) DEFAULT NULL,
  `value` mediumint(9) NOT NULL,
  `btype` tinyint(4) NOT NULL,
  `money` mediumint(9) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `bizcargo`
--

DROP TABLE IF EXISTS `bizcargo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bizcargo` (
  `id` mediumint(9) NOT NULL,
  `fk` smallint(6) NOT NULL,
  `cargo` tinyint(3) unsigned NOT NULL,
  `qnty` smallint(6) NOT NULL,
  `value` smallint(6) NOT NULL,
  `pickup` smallint(6) NOT NULL,
  `assigned` smallint(6) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `cfk_idx` (`fk`),
  CONSTRAINT `cafk` FOREIGN KEY (`fk`) REFERENCES `biz` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `bizstock`
--

DROP TABLE IF EXISTS `bizstock`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bizstock` (
  `sid` mediumint(9) NOT NULL,
  `sfk` smallint(6) NOT NULL,
  `sitem` tinyint(4) unsigned NOT NULL,
  `samount` smallint(6) NOT NULL,
  `svalue` smallint(6) NOT NULL,
  PRIMARY KEY (`sid`),
  KEY `bsfk_idx` (`sfk`),
  CONSTRAINT `bsfk` FOREIGN KEY (`sfk`) REFERENCES `biz` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `building`
--

DROP TABLE IF EXISTS `building`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `building` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `owner` mediumint(9) DEFAULT NULL,
  `value` mediumint(9) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `aps` tinyint(4) DEFAULT NULL,
  `name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `carstats`
--

DROP TABLE IF EXISTS `carstats`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `carstats` (
  `id` tinyint(4) unsigned NOT NULL,
  `name` varchar(15) NOT NULL,
  `price` mediumint(9) NOT NULL,
  `devalue` float NOT NULL,
  `fueltyp` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `crimes`
--

DROP TABLE IF EXISTS `crimes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `crimes` (
  `fk` mediumint(9) NOT NULL,
  `crime` varchar(45) NOT NULL,
  `rhl` smallint(6) NOT NULL,
  PRIMARY KEY (`fk`),
  CONSTRAINT `ucrime` FOREIGN KEY (`fk`) REFERENCES `players` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employee` (
  `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `biz` smallint(6) NOT NULL,
  `user` mediumint(9) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `empfk_idx` (`biz`),
  CONSTRAINT `empfk` FOREIGN KEY (`biz`) REFERENCES `biz` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `garage`
--

DROP TABLE IF EXISTS `garage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `garage` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `isbuilding` smallint(6) DEFAULT NULL,
  `ishouse` smallint(6) DEFAULT NULL,
  `isBiz` smallint(6) DEFAULT NULL,
  `gx` float NOT NULL,
  `gy` float NOT NULL,
  `gz` float NOT NULL,
  `grx` float NOT NULL,
  `gry` float NOT NULL,
  `grz` float NOT NULL,
  `cars` tinyint(4) NOT NULL,
  `typ` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `hfriends`
--

DROP TABLE IF EXISTS `hfriends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hfriends` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `hffk` smallint(6) NOT NULL,
  `friend` mediumint(9) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `hff_idx` (`hffk`),
  CONSTRAINT `hff` FOREIGN KEY (`hffk`) REFERENCES `house` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `fk` mediumint(9) NOT NULL,
  `staff` mediumint(9) NOT NULL,
  `typ` tinyint(4) NOT NULL,
  `reason` varchar(40) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `uhistory_idx` (`fk`),
  CONSTRAINT `uhistory` FOREIGN KEY (`fk`) REFERENCES `players` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `house`
--

DROP TABLE IF EXISTS `house`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `house` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `fk` smallint(6) DEFAULT NULL,
  `owner` mediumint(9) DEFAULT NULL,
  `value` mediumint(9) NOT NULL,
  `money` mediumint(9) NOT NULL,
  `bought` date DEFAULT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `hrent`
--

DROP TABLE IF EXISTS `hrent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hrent` (
  `fk` mediumint(9) NOT NULL AUTO_INCREMENT,
  `renting` mediumint(9) NOT NULL,
  `value` smallint(6) NOT NULL,
  `pay` datetime NOT NULL,
  `contract` datetime NOT NULL,
  PRIMARY KEY (`fk`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `hspawn`
--

DROP TABLE IF EXISTS `hspawn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hspawn` (
  `fk` smallint(6) NOT NULL,
  `ix` float DEFAULT NULL,
  `iy` float DEFAULT NULL,
  `iz` float DEFAULT NULL,
  PRIMARY KEY (`fk`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `item`
--

DROP TABLE IF EXISTS `item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `item` (
  `ipk` int(11) NOT NULL,
  `ifk` mediumint(9) NOT NULL,
  `svtyp` tinyint(1) NOT NULL DEFAULT '0',
  `item` tinyint(3) unsigned NOT NULL,
  `size` smallint(5) unsigned NOT NULL,
  PRIMARY KEY (`ipk`),
  KEY `itemindex` (`ifk`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `players` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `user` varchar(22) NOT NULL,
  `pass` char(64) NOT NULL,
  `cash` mediumint(9) NOT NULL DEFAULT '1000000',
  `skin` varchar(34) NOT NULL DEFAULT '0',
  `made` datetime NOT NULL,
  `vehicle` smallint(6) DEFAULT NULL,
  `job` tinyint(4) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `select` (`user`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pvehicles`
--

DROP TABLE IF EXISTS `pvehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pvehicles` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `fk` mediumint(9) DEFAULT NULL,
  `model` tinyint(3) unsigned NOT NULL,
  `fuel` tinyint(4) NOT NULL DEFAULT '100',
  `c1` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `c2` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `c3` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `c4` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `km` float NOT NULL DEFAULT '0',
  `store` smallint(6) NOT NULL DEFAULT '-1',
  `pos` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `owner_idx` (`fk`),
  CONSTRAINT `owner` FOREIGN KEY (`fk`) REFERENCES `players` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `skins`
--

DROP TABLE IF EXISTS `skins`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `skins` (
  `id` smallint(6) NOT NULL,
  `biz` tinyint(3) unsigned NOT NULL,
  `price` smallint(6) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `spawn`
--

DROP TABLE IF EXISTS `spawn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spawn` (
  `fk` mediumint(9) NOT NULL,
  `x` float NOT NULL DEFAULT '2286.9',
  `y` float NOT NULL DEFAULT '495.6',
  `z` float NOT NULL DEFAULT '5.6',
  `last` datetime NOT NULL,
  `jskin` varchar(34) DEFAULT NULL,
  PRIMARY KEY (`fk`),
  CONSTRAINT `uspawn` FOREIGN KEY (`fk`) REFERENCES `players` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `stveh`
--

DROP TABLE IF EXISTS `stveh`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stveh` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `owner` tinyint(4) NOT NULL,
  `model` tinyint(4) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `rx` float NOT NULL,
  `ry` float NOT NULL,
  `rz` float NOT NULL,
  `co` tinyint(3) unsigned NOT NULL,
  `ct` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=328 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tunes`
--

DROP TABLE IF EXISTS `tunes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tunes` (
  `id` smallint(6) NOT NULL AUTO_INCREMENT,
  `fk` smallint(6) NOT NULL,
  `slot` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `vfk_idx` (`fk`),
  CONSTRAINT `vfk` FOREIGN KEY (`fk`) REFERENCES `pvehicles` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `wardrobe`
--

DROP TABLE IF EXISTS `wardrobe`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `wardrobe` (
  `id` mediumint(9) NOT NULL,
  `fk` smallint(6) NOT NULL,
  `model` varchar(34) NOT NULL,
  `alias` varchar(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `whouse_idx` (`fk`),
  CONSTRAINT `whouse` FOREIGN KEY (`fk`) REFERENCES `house` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-01-31 13:38:31
