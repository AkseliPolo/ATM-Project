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
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (2,2,1200.00,500.00,NULL),(4,2,1000.00,500.00,NULL),(7,6,1000.00,NULL,NULL),(8,6,1000.00,NULL,NULL),(10,6,1000.00,500.00,0.00),(11,18,1000.00,500.00,0.00);
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
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `cardNumber_UNIQUE` (`cardNumber`),
  KEY `Account_Card_idx` (`idAccount`),
  CONSTRAINT `Account_Card` FOREIGN KEY (`idAccount`) REFERENCES `account` (`idAccount`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (23,2,'234718256','$2b$12$7e44f5dFaM6eopkV1ZAO1uvTJDzBgoCjkwzGJktU/QGqLVX4.gmt2','2026-12-31','debit'),(24,2,'23471844256','$2b$12$SBYi3eAKa.eIH2CAGWq3HeFDq8wS.HdWotwPTHquFh9ogVmRsXQzG','2026-12-31','debit'),(25,2,'234711844256','$2b$12$J3KUup2DCe8RLI1LOQu5ueGEpt7OEi83MU7AqFQ0QztLaoTLt0em.','2026-12-31','debit'),(26,2,'23471184425655','$2b$12$wcAoacsR9eXUbzSWQb0gne92fjAz.QsLxu5JuQzJx0c7fAy8tLJYS','2026-12-31','debit'),(27,2,'2347184425655','$2b$12$6OyOqsmFWS.VvT26gvG6xeW/v0RVNeWVUDn2sHOrG.JmWyDbqs75C','2026-12-31','debit'),(28,2,'1','$2b$12$4L81BZUgi5oWPAXSN.YGLODNKIar3Y/8.Dw38OgAhtPrmEkuHjLyC','2026-12-31','debit'),(29,2,'12','$2b$12$CAC6c1/JvVYuO03E9SKClOfpDv3IO32skMnWVjG4VbVYF9WGIgKKS','2026-12-31','debit'),(31,2,'102','2222','2026-12-31','debit'),(32,2,'1022','$2b$12$qk1aMd1V9JfWCMEVyCxsLeRORCp8yjnblmU81rqaz5BlceCopRqSq','2026-12-31','debit'),(33,2,'1011','$2b$12$nXcMkL.RhIZBlQhqiIajN.ui.qppQhJYlpLvcTADO.w97XIxmxd36','2026-12-31','debit'),(34,11,'6666','$2b$12$BWGvPJKk.kzq089RVc0PceITOQuAw1DbMU/w129JMaUp3tZATrZB.','2026-12-31','credit');
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
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customers`
--

LOCK TABLES `customers` WRITE;
/*!40000 ALTER TABLE `customers` DISABLE KEYS */;
INSERT INTO `customers` VALUES (2,'pekka','esim',NULL),(4,'pertti','kurikka',NULL),(5,'matti','matti','matti'),(6,'eero','kujala',NULL),(7,'maria','kujala',NULL),(8,'maria','salo',NULL),(9,'maria','pekkanen',NULL),(10,'maria','pekkaien',NULL),(12,'Robert','Pudas','koti'),(13,'Robert','Pudas','koti'),(14,'Robert','Pudas','koti'),(15,'Robert','Pudas','koti'),(16,'Robert','Pudas','koti'),(17,'Robert','Pudas','koti'),(18,'Robert','Pudas','terve');
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
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (2,2,100.00,'deposit','2026-03-30 09:21:30'),(3,2,100.00,'deposit','2026-03-30 09:34:45'),(4,2,100.00,'deposit',NULL),(6,2,100.00,'deposit',NULL),(8,7,100.00,'deposit',NULL),(9,7,100.00,'deposit','1990-05-12 00:00:00');
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

-- Dump completed on 2026-04-07 10:04:54
