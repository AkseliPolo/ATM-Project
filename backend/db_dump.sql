CREATE DATABASE  IF NOT EXISTS `bank_db` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bank_db`;
-- MySQL dump 10.13  Distrib 8.0.44, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bank_db
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `idAccount` int NOT NULL AUTO_INCREMENT,
  `idCustomer` int DEFAULT NULL,
  `balance` decimal(10,2) DEFAULT NULL,
  `credit_limit` decimal(10,2) DEFAULT NULL,
  `credit_used` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`idAccount`),
  KEY `CustomersAccount_idx` (`idCustomer`),
  CONSTRAINT `Customers_Account` FOREIGN KEY (`idCustomer`) REFERENCES `customers` (`idCustomers`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (2,2,1200.00,500.00,NULL),(4,2,1000.00,500.00,NULL),(7,6,1000.00,NULL,NULL),(8,6,1000.00,NULL,NULL),(10,6,1000.00,500.00,0.00),(11,18,49999910.00,500.00,0.00),(12,18,1000.00,500.00,0.00),(13,19,7170.00,5000.00,0.00);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL AUTO_INCREMENT,
  `idAccount` int DEFAULT NULL,
  `cardNumber` varchar(100) DEFAULT NULL,
  `pin` varchar(255) DEFAULT NULL,
  `expiry_date` date DEFAULT NULL,
  `card_type` enum('debit','credit') DEFAULT NULL,
  `card_locked` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `cardNumber_UNIQUE` (`cardNumber`),
  KEY `Account_Card_idx` (`idAccount`),
  CONSTRAINT `Account_Card` FOREIGN KEY (`idAccount`) REFERENCES `account` (`idAccount`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (23,2,'234718256','$2b$12$7e44f5dFaM6eopkV1ZAO1uvTJDzBgoCjkwzGJktU/QGqLVX4.gmt2','2026-12-31','debit',0),(24,2,'23471844256','$2b$12$SBYi3eAKa.eIH2CAGWq3HeFDq8wS.HdWotwPTHquFh9ogVmRsXQzG','2026-12-31','debit',0),(25,2,'234711844256','$2b$12$J3KUup2DCe8RLI1LOQu5ueGEpt7OEi83MU7AqFQ0QztLaoTLt0em.','2026-12-31','debit',0),(26,2,'23471184425655','$2b$12$wcAoacsR9eXUbzSWQb0gne92fjAz.QsLxu5JuQzJx0c7fAy8tLJYS','2026-12-31','debit',0),(27,2,'2347184425655','$2b$12$6OyOqsmFWS.VvT26gvG6xeW/v0RVNeWVUDn2sHOrG.JmWyDbqs75C','2026-12-31','debit',0),(28,2,'1','$2b$12$4L81BZUgi5oWPAXSN.YGLODNKIar3Y/8.Dw38OgAhtPrmEkuHjLyC','2026-12-31','debit',0),(29,2,'12','$2b$12$CAC6c1/JvVYuO03E9SKClOfpDv3IO32skMnWVjG4VbVYF9WGIgKKS','2026-12-31','debit',0),(31,2,'102','2222','2026-12-31','debit',0),(32,2,'1022','$2b$12$qk1aMd1V9JfWCMEVyCxsLeRORCp8yjnblmU81rqaz5BlceCopRqSq','2026-12-31','debit',0),(33,2,'1011','$2b$12$nXcMkL.RhIZBlQhqiIajN.ui.qppQhJYlpLvcTADO.w97XIxmxd36','2026-12-31','debit',0),(34,11,'6666','$2b$12$BWGvPJKk.kzq089RVc0PceITOQuAw1DbMU/w129JMaUp3tZATrZB.','2026-12-31','credit',0),(35,11,'6767','$2b$12$TEzfgfpWYwEz.cZw3MMiAOD/OxrWD3FfcCZ6ZgaXx7P.fSXThAQWK','2026-12-31','debit',0),(38,13,'7777','$2b$12$EKH5QpP8UY50TyY/28Rtk.mdG3HRqcZ4IQQ/rMkx2wcjM5vx7HcWK','2026-12-31','credit',0),(39,13,'8888','$2b$12$vPNR9vM50onFVtfjaw88AOmLAdj0oRfNoFaWE2g3afT/6Uu9HAx9m','2026-12-31','debit',0);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customers`
--

DROP TABLE IF EXISTS `customers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customers` (
  `idCustomers` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(20) DEFAULT NULL,
  `lname` varchar(20) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idCustomers`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customers`
--

LOCK TABLES `customers` WRITE;
/*!40000 ALTER TABLE `customers` DISABLE KEYS */;
INSERT INTO `customers` VALUES (2,'pekka','esim',NULL),(4,'pertti','kurikka',NULL),(5,'matti','matti','matti'),(6,'eero','kujala',NULL),(7,'maria','kujala',NULL),(8,'maria','salo',NULL),(9,'maria','pekkanen',NULL),(10,'maria','pekkaien',NULL),(18,'Robert','Pudas','terve'),(19,'Eero','Laurila','Oulunkuja 15');
/*!40000 ALTER TABLE `customers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `idtransaction` int NOT NULL AUTO_INCREMENT,
  `idAccount` int DEFAULT NULL,
  `amount` decimal(10,2) DEFAULT NULL,
  `type` varchar(45) DEFAULT NULL,
  `date` datetime DEFAULT NULL,
  PRIMARY KEY (`idtransaction`),
  KEY `Account_Transaction` (`idAccount`),
  CONSTRAINT `Account_Transaction` FOREIGN KEY (`idAccount`) REFERENCES `account` (`idAccount`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=136 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (2,2,100.00,'deposit','2026-03-30 09:21:30'),(3,2,100.00,'deposit','2026-03-30 09:34:45'),(4,2,100.00,'deposit',NULL),(6,2,100.00,'deposit',NULL),(8,7,100.00,'deposit',NULL),(9,7,100.00,'deposit','1990-05-12 00:00:00'),(10,7,100.00,'deposit','1990-05-12 00:00:00'),(11,11,100.00,'deposit','2026-04-08 17:00:19'),(12,11,100.00,'deposit','2026-04-08 17:01:11'),(13,11,500.00,'withdraw','2026-04-08 17:01:36'),(14,11,800.00,'withdraw','2026-04-08 17:02:56'),(15,11,100.00,'withdraw','2026-04-08 17:04:41'),(16,11,300.00,'withdraw','2026-04-08 17:05:13'),(17,11,1000.00,'deposit','2026-04-08 17:06:09'),(18,11,500.00,'withdraw','2026-04-08 17:11:26'),(19,11,1000000.00,'deposit','2026-04-08 17:13:29'),(20,11,1000000.00,'deposit','2026-04-09 09:05:10'),(21,11,1000000.00,'deposit','2026-04-09 09:08:58'),(22,11,3000000.00,'withdraw','2026-04-09 09:09:28'),(23,11,500.00,'withdraw','2026-04-09 09:10:52'),(24,11,500.00,'deposit','2026-04-09 09:35:02'),(25,11,500.00,'deposit','2026-04-09 09:38:04'),(26,11,500.00,'deposit','2026-04-09 09:40:27'),(27,11,500.00,'deposit','2026-04-09 09:45:06'),(28,11,500.00,'deposit','2026-04-09 09:50:44'),(29,11,500.00,'withdraw','2026-04-09 09:50:51'),(30,11,500.00,'deposit','2026-04-09 09:52:05'),(31,11,500.00,'withdraw','2026-04-09 10:05:30'),(32,11,500.00,'deposit','2026-04-09 10:47:09'),(33,11,500.00,'withdraw','2026-04-09 10:47:16'),(34,11,200.00,'deposit','2026-04-09 10:47:58'),(35,11,300.00,'deposit','2026-04-09 10:50:58'),(36,11,300.00,'deposit','2026-04-09 10:57:24'),(37,11,600.00,'deposit','2026-04-09 10:58:32'),(38,11,600.00,'deposit','2026-04-09 11:00:31'),(39,11,600.00,'deposit','2026-04-09 11:01:29'),(40,11,2200.00,'withdraw','2026-04-09 11:01:50'),(41,11,50.00,'deposit','2026-04-09 11:02:17'),(42,11,10.00,'withdraw','2026-04-09 11:02:45'),(43,11,10.00,'deposit','2026-04-09 11:04:48'),(44,11,500.00,'deposit','2026-04-09 11:05:01'),(45,11,500.00,'deposit','2026-04-09 11:08:38'),(46,11,1000.00,'withdraw','2026-04-09 11:09:05'),(47,11,1000.00,'deposit','2026-04-09 11:10:54'),(48,11,1000.00,'deposit','2026-04-09 11:11:57'),(49,11,2000.00,'withdraw','2026-04-09 11:12:16'),(50,11,200.00,'withdraw','2026-04-09 11:13:22'),(51,11,200.00,'deposit','2026-04-09 11:13:39'),(52,11,2000.00,'deposit','2026-04-09 11:13:54'),(53,11,200.00,'deposit','2026-04-09 11:14:51'),(54,11,2500.00,'withdraw','2026-04-09 11:15:10'),(55,11,20.00,'deposit','2026-04-09 11:20:57'),(56,11,200.00,'deposit','2026-04-09 11:21:15'),(57,11,200.00,'deposit','2026-04-09 11:21:25'),(58,11,200.00,'deposit','2026-04-09 11:22:14'),(59,11,500.00,'withdraw','2026-04-09 11:22:33'),(60,11,500.00,'deposit','2026-04-09 11:22:49'),(61,11,500.00,'withdraw','2026-04-09 11:23:42'),(62,11,500.00,'deposit','2026-04-09 11:24:02'),(63,11,270.00,'withdraw','2026-04-09 11:24:24'),(64,11,270.00,'withdraw','2026-04-09 11:24:35'),(65,11,500.00,'deposit','2026-04-09 11:24:53'),(66,11,500.00,'withdraw','2026-04-09 11:27:35'),(67,11,500.00,'deposit','2026-04-09 11:27:52'),(68,11,500.00,'deposit','2026-04-09 11:30:07'),(69,11,500.00,'deposit','2026-04-09 11:30:20'),(70,11,500.00,'withdraw','2026-04-09 11:30:35'),(71,11,1000.00,'withdraw','2026-04-09 11:30:49'),(72,11,500.00,'deposit','2026-04-09 11:31:08'),(73,11,700.00,'deposit','2026-04-09 11:31:35'),(74,11,700.00,'withdraw','2026-04-09 11:32:51'),(75,11,700.00,'withdraw','2026-04-09 11:33:04'),(76,11,700.00,'deposit','2026-04-09 11:34:46'),(77,11,700.00,'withdraw','2026-04-09 11:35:10'),(78,11,700.00,'deposit','2026-04-09 11:36:06'),(79,11,700.00,'withdraw','2026-04-09 11:36:22'),(80,11,700.00,'deposit','2026-04-09 11:38:22'),(81,11,700.00,'withdraw','2026-04-09 11:40:10'),(82,11,700.00,'deposit','2026-04-09 11:40:25'),(83,11,700.00,'withdraw','2026-04-09 11:42:50'),(84,11,700.00,'deposit','2026-04-09 11:43:03'),(85,11,700.00,'deposit','2026-04-09 11:43:20'),(86,11,700.00,'withdraw','2026-04-09 11:43:38'),(87,11,700.00,'withdraw','2026-04-09 11:43:48'),(88,11,700.00,'deposit','2026-04-09 11:44:03'),(89,11,30.00,'deposit','2026-04-09 11:44:18'),(90,11,500.00,'withdraw','2026-04-09 11:49:50'),(91,11,500.00,'deposit','2026-04-09 11:50:07'),(92,11,400.00,'deposit','2026-04-09 11:50:22'),(93,11,600.00,'withdraw','2026-04-09 11:50:39'),(94,11,500.00,'withdraw','2026-04-09 11:50:54'),(95,11,50.00,'deposit','2026-04-09 11:51:11'),(96,11,500.00,'deposit','2026-04-09 11:52:11'),(97,11,1500.00,'deposit','2026-04-09 11:52:53'),(98,11,1500.00,'deposit','2026-04-09 11:53:39'),(99,11,200.00,'withdraw','2026-04-09 11:53:59'),(100,11,3000.00,'withdraw','2026-04-09 12:11:36'),(101,11,50000000.00,'deposit','2026-04-09 15:29:10'),(102,13,50.00,'deposit','2026-04-09 15:36:53'),(103,13,3000.00,'withdraw','2026-04-09 15:37:31'),(104,13,2050.00,'withdraw','2026-04-09 15:38:06'),(105,13,10000.00,'deposit','2026-04-09 15:39:31'),(106,13,50.00,'withdraw','2026-04-09 16:01:30'),(107,13,70.00,'withdraw','2026-04-09 16:01:55'),(108,13,70.00,'withdraw','2026-04-09 16:05:55'),(109,13,7.00,'deposit','2026-04-09 16:06:13'),(110,13,7.00,'deposit','2026-04-09 16:09:47'),(111,13,70.00,'withdraw','2026-04-09 16:10:21'),(112,13,5.00,'deposit','2026-04-10 12:49:30'),(113,13,100.00,'deposit','2026-04-10 12:53:12'),(114,13,5.00,'deposit','2026-04-10 12:53:21'),(115,13,5.00,'deposit','2026-04-10 12:55:12'),(116,13,50.00,'deposit','2026-04-10 12:55:15'),(117,13,50.00,'deposit','2026-04-10 12:56:36'),(118,13,75.00,'deposit','2026-04-10 12:56:42'),(119,13,700.00,'deposit','2026-04-10 12:57:01'),(120,13,700.00,'deposit','2026-04-10 14:14:41'),(121,13,700.00,'deposit','2026-04-10 17:42:52'),(122,13,700.00,'deposit','2026-04-10 17:44:39'),(123,13,700.00,'deposit','2026-04-10 17:45:02'),(124,13,700.00,'withdraw','2026-04-10 17:45:31'),(125,13,7.00,'deposit','2026-04-10 17:46:19'),(126,13,700.00,'withdraw','2026-04-10 17:47:12'),(127,13,700.00,'withdraw','2026-04-10 17:47:32'),(128,13,7.00,'deposit','2026-04-10 17:48:14'),(129,13,600.00,'deposit','2026-04-10 18:08:35'),(130,13,67.00,'deposit','2026-04-10 18:08:55'),(131,13,60.00,'withdraw','2026-04-10 18:09:31'),(132,13,60.00,'withdraw','2026-04-10 18:10:37'),(133,13,65.00,'deposit','2026-04-10 18:11:10'),(134,13,50.00,'deposit','2026-04-10 18:11:33'),(135,13,50.00,'deposit','2026-04-10 18:11:50');
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-04-13  8:58:08
