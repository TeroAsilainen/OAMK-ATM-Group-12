-- MySQL dump 10.13  Distrib 8.0.40, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bankdb
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
  `idaccount` varchar(18) NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `credit_limit` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`idaccount`),
  UNIQUE KEY `idaccount_UNIQUE` (`idaccount`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES ('12',564.00,2000.00),('123',510.00,1000.00),('FI0012345678910112',510.00,0.00),('FI0123450060678910',478.20,1000.00),('FI0123456789123456',2122.88,0.00),('FI021345006098701',364.00,2000.00),('FI031245006087910',725.24,0.00),('FI1098765432154321',2475.80,0.00),('FI1234567891000001',595959.76,596479.76),('FI1234567891000002',-419.54,-449.54),('FI1234567891000003',16112.16,0.00),('FI1234567891112135',564.00,2000.00);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_user`
--

DROP TABLE IF EXISTS `account_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_user` (
  `idaccount_user` int NOT NULL AUTO_INCREMENT,
  `idaccount` varchar(18) NOT NULL,
  `iduser` int NOT NULL,
  `idowner` int DEFAULT NULL,
  PRIMARY KEY (`idaccount_user`),
  KEY `idaccount_idx` (`idaccount`),
  KEY `iduser_idx` (`iduser`),
  KEY `owner_account_user_idx` (`idowner`),
  CONSTRAINT `account_account_user` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `owner_account_user` FOREIGN KEY (`idowner`) REFERENCES `user` (`iduser`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `user_account_user` FOREIGN KEY (`iduser`) REFERENCES `user` (`iduser`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_user`
--

LOCK TABLES `account_user` WRITE;
/*!40000 ALTER TABLE `account_user` DISABLE KEYS */;
INSERT INTO `account_user` VALUES (1,'FI0012345678910112',767043508,767043508),(2,'FI0123450060678910',901960512,901960512),(3,'FI031245006087910',771759321,771759321),(4,'FI1234567891000001',771759321,771759321),(5,'FI0123456789123456',898837085,898837085),(6,'FI0123456789123456',898837084,898837085),(7,'FI1098765432154321',901960512,901960512),(8,'FI1234567891000003',577901750,577901750),(9,'FI1234567891000002',577901750,577901750);
/*!40000 ALTER TABLE `account_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL,
  `pin` varchar(255) DEFAULT NULL,
  `cardtype` int NOT NULL,
  `wrong_attempts` int DEFAULT NULL,
  `iduser` int NOT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `idcard_UNIQUE` (`idcard`),
  KEY `iduser_idx` (`iduser`),
  CONSTRAINT `user_card` FOREIGN KEY (`iduser`) REFERENCES `user` (`iduser`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (10001000,'$2a$10$6aDZXFodvuZnGMXeH6e6k.valoq3lRe91rzo2asmhIucbc.dZFW32',1,0,767043508),(10101010,'$2a$10$OU0bw94EVmKD.z3Xi1gtFeS/VHB39gQopbGLI1Pj9XcvAtYmCoiCe',3,0,771759321),(12341234,'$2a$10$I5TZn2GKLulGpbQgTDGnH.KSPP00MeTAR1tLgCtaZlTph7tZko2.W',2,0,901960512),(22222222,'$2a$10$UEQlOR0vXuGQHmx1Efrxw.0tliMgTFg3ozsXyIQGvmvoj/VXnM8uG',1,0,898837085),(33333333,'$2a$10$jy/L8I6qAs.gUV4VdHyOHOKmpK/6F8CH4zzf4Nx5WiUdWocuELe4q',1,0,898837084),(44444444,'$2a$10$wHAdLhLd3TdwKrXmcHDNWuzOTM2zqpyhUnP39l6DYpgIfkO.h5sxi',3,0,577901750);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card_account`
--

DROP TABLE IF EXISTS `card_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card_account` (
  `idcard_account` int NOT NULL AUTO_INCREMENT,
  `idcard` int NOT NULL,
  `idaccount` varchar(18) NOT NULL,
  PRIMARY KEY (`idcard_account`),
  KEY `idcard_idx` (`idcard`),
  KEY `idaccount_idx` (`idaccount`),
  CONSTRAINT `account_card_account` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `card_card_account` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card_account`
--

LOCK TABLES `card_account` WRITE;
/*!40000 ALTER TABLE `card_account` DISABLE KEYS */;
INSERT INTO `card_account` VALUES (1,10001000,'FI0012345678910112'),(2,12341234,'FI0123450060678910'),(3,10101010,'FI031245006087910'),(4,10101010,'FI1234567891000001'),(5,22222222,'FI0123456789123456'),(6,33333333,'FI0123456789123456'),(7,44444444,'FI1234567891000003'),(8,44444444,'FI1234567891000002');
/*!40000 ALTER TABLE `card_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `idtransaction` int NOT NULL AUTO_INCREMENT,
  `idaccount` varchar(18) NOT NULL,
  `date` timestamp NULL DEFAULT NULL,
  `action` varchar(45) DEFAULT NULL,
  `amount` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`idtransaction`),
  UNIQUE KEY `idtransaction_UNIQUE` (`idtransaction`),
  KEY `idaccount_idx` (`idaccount`),
  CONSTRAINT `account_transaction` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=73 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,'FI1234567891000001','2025-01-17 11:16:20','Nosto',300.00),(2,'FI1234567891000001','2025-01-17 11:17:07','Nosto',568.00),(3,'FI1234567891000001','2025-01-21 22:00:00','Nosto',400.00),(5,'FI1234567891000002','2025-01-17 11:18:20','Talletus',300.00),(6,'FI1234567891000001','2025-01-17 11:55:41','Nosto',300.00),(7,'FI1234567891000002','2025-01-17 11:55:41','Talletus',300.00),(8,'FI1234567891000002','2025-01-17 11:59:45','Nosto',568.00),(9,'FI1234567891000002','2025-01-17 12:01:15','Nosto',568.00),(10,'FI1234567891000002','2025-01-17 12:04:55','Nosto',568.00),(11,'FI1234567891000002','2025-01-17 12:06:05','Nosto',568.00),(12,'FI1234567891000002','2025-01-17 12:07:09','Nosto',568.00),(13,'FI1234567891000002','2025-01-17 12:11:01','Nosto',9000.00),(14,'FI1234567891000001','2025-01-17 12:11:01','Talletus',9000.00),(15,'FI1234567891000002','2025-01-17 12:16:59','Nosto',200.00),(16,'FI1234567891000002','2025-02-05 15:57:03','Nosto',10.00),(17,'FI1234567891000002','2025-02-05 16:00:23','Nosto',1.00),(18,'FI1234567891000002','2025-02-05 16:06:28','Nosto',0.50),(19,'FI0123450060678910','2025-02-06 08:02:08','Nosto',1.00),(20,'FI0123450060678910','2025-02-06 08:02:16','Nosto',2.00),(21,'FI0123450060678910','2025-02-06 08:02:23','Nosto',2.00),(22,'FI0123450060678910','2025-02-06 08:02:25','Nosto',2.00),(23,'FI0123450060678910','2025-02-06 08:02:26','Nosto',2.00),(24,'FI0123450060678910','2025-02-06 08:02:26','Nosto',2.00),(25,'FI0123450060678910','2025-02-06 08:02:27','Nosto',2.00),(26,'FI0123450060678910','2025-02-06 08:02:27','Nosto',2.00),(27,'FI0123450060678910','2025-02-06 08:02:27','Nosto',2.00),(28,'FI0123450060678910','2025-02-06 08:02:27','Nosto',2.00),(29,'FI0123450060678910','2025-02-06 08:02:27','Nosto',2.00),(30,'FI0123450060678910','2025-02-06 08:02:28','Nosto',2.00),(31,'FI0123450060678910','2025-02-06 08:02:28','Nosto',2.00),(32,'FI0123450060678910','2025-02-06 08:02:28','Nosto',2.00),(33,'FI0123450060678910','2025-02-06 08:02:28','Nosto',2.00),(34,'FI0123450060678910','2025-02-06 08:02:28','Nosto',2.00),(35,'FI0123450060678910','2025-02-06 08:02:29','Nosto',2.00),(36,'FI0123450060678910','2025-02-06 08:02:29','Nosto',2.00),(37,'FI0123450060678910','2025-02-06 08:02:29','Nosto',2.00),(38,'FI0123450060678910','2025-02-06 08:02:29','Nosto',2.00),(39,'FI0123450060678910','2025-02-06 08:02:29','Nosto',2.00),(40,'FI0123450060678910','2025-02-06 08:02:30','Nosto',2.00),(41,'FI0123450060678910','2025-02-06 10:08:40','Nosto',2.00),(42,'FI0123450060678910','2025-02-06 10:08:43','Nosto',2.00),(43,'FI0123450060678910','2025-02-06 10:45:05','Nosto',2.00),(44,'FI0123450060678910','2025-02-06 10:45:06','Nosto',2.00),(45,'FI0123450060678910','2025-02-06 11:11:43','Nosto',5.00),(46,'FI0123450060678910','2025-02-16 08:50:44','Nosto',12.80),(47,'FI1098765432154321','2025-02-16 08:50:44','Talletus',12.80),(48,'FI1098765432154321','2025-02-16 08:51:42','Nosto',50.00),(49,'FI0123450060678910','2025-02-16 08:51:42','Talletus',50.00),(50,'FI0123456789123456','2025-02-16 08:54:41','Nosto',0.12),(51,'FI1234567891000002','2025-02-16 08:54:41','Talletus',0.12),(52,'FI1234567891000002','2025-02-16 09:16:47','Nosto',0.04),(53,'FI1234567891000003','2025-02-16 09:16:47','Talletus',0.04),(54,'FI1234567891000002','2025-02-16 09:21:03','Nosto',0.12),(55,'FI1234567891000003','2025-02-16 09:21:03','Talletus',0.12),(56,'FI1234567891000001','2025-02-16 09:27:12','Nosto',0.12),(57,'FI031245006087910','2025-02-16 09:27:12','Talletus',0.12),(58,'FI1234567891000001','2025-02-16 09:30:33','Nosto',0.12),(59,'FI031245006087910','2025-02-16 09:30:33','Talletus',0.12),(60,'FI1234567891000002','2025-02-16 09:31:14','Nosto',16000.00),(61,'FI1234567891000003','2025-02-16 09:31:14','Talletus',16000.00),(62,'FI1234567891000003','2025-02-16 09:33:26','Nosto',45.00),(63,'FI1234567891000002','2025-02-16 09:33:26','Talletus',45.00),(64,'FI0123450060678910','2025-02-16 09:43:32','Nosto',13.00),(65,'FI1098765432154321','2025-02-16 09:43:32','Talletus',13.00),(66,'FI1234567891000001','2025-02-16 09:44:29','Nosto',45.00),(67,'FI031245006087910','2025-02-16 09:44:29','Talletus',45.00),(68,'FI1234567891000002','2025-02-17 11:35:13','Nosto',30.00),(69,'FI1234567891000001','2025-02-17 11:36:17','Nosto',30.00),(70,'FI1234567891000001','2025-02-17 11:37:09','Nosto',30.00),(71,'FI1234567891000001','2025-02-17 11:37:33','Nosto',170.00),(72,'FI1234567891000001','2025-02-17 11:41:25','Nosto',350.00);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `iduser` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) DEFAULT NULL,
  `lname` varchar(45) DEFAULT NULL,
  `phonenumber` varchar(20) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`iduser`),
  UNIQUE KEY `iduser_UNIQUE` (`iduser`)
) ENGINE=InnoDB AUTO_INCREMENT=901960513 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (577901750,'Sari','Nieminen','045-4567890','Kivitie 3b, 20100 Turku'),(767043508,'Mikko','Mäkinen','040-1234567','Mäkikatu 12, 00100 Helsinki'),(771759321,'Janne','Korhonen','041-3456789','Metsäpolku 8 A 32, 90100 Oulu'),(898837084,'Antti','Virtanen','044-5678901','Auringonlaskuntie 7 C 2, 40100 Jyväskylä'),(898837085,'Amanda','Virtanen','044-5678902','Auringonlaskuntie 7 C 2, 40100 Jyväskylä'),(901960512,'Laura','Lehtinen','050-2345678','Rantatie 5, 33100 Tampere');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bankdb'
--
/*!50003 DROP PROCEDURE IF EXISTS `credit_transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_transfer`(IN first_id VARCHAR(18), IN second_id VARCHAR(18), IN amount DECIMAL(10,2) )
BEGIN
  DECLARE test1, test2 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET balance=balance-amount WHERE idaccount=first_id AND balance + credit_limit >= amount;
  SET test1=ROW_COUNT();
  UPDATE account SET balance=balance+amount WHERE idaccount=second_id;
  SET test2=ROW_COUNT();
    IF (test1 > 0 AND test2 >0) THEN
      COMMIT;
      INSERT INTO transaction(idaccount,action,amount,date) VALUES(first_id,'Nosto',amount, NOW());
      INSERT INTO transaction(idaccount,action,amount,date) VALUES(second_id,'Talletus',amount, NOW());
    ELSE
      ROLLBACK;
END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `credit_withdrawal` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_withdrawal`(IN first_id VARCHAR(18), IN amount DECIMAL(10,2) )
BEGIN
  DECLARE test1, test2 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET balance=balance-amount WHERE idaccount=first_id AND credit_limit >= amount;
  SET test1=ROW_COUNT();
    IF (test1 > 0 ) THEN
      COMMIT;
      INSERT INTO transaction(idaccount,date,action,amount) VALUES(first_id,NOW(),'Nosto',amount);
    ELSE
      ROLLBACK;
END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `debit_transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_transfer`(IN first_id VARCHAR(18), IN second_id VARCHAR(18), IN amount DECIMAL(10,2) )
BEGIN
  DECLARE test1,test2 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET balance=balance-amount WHERE idaccount=first_id AND balance >= amount;
  SET test1=ROW_COUNT();
  UPDATE account SET balance=balance+amount WHERE idaccount=second_id;
  SET test2=ROW_COUNT();
    IF (test1 > 0 AND test2 >0) THEN   
      COMMIT;    
      INSERT INTO transaction(idaccount,action,amount,date) VALUES(first_id,'Nosto',amount,NOW());
      INSERT INTO transaction(idaccount,action,amount,date) VALUES(second_id,'Talletus',amount,NOW());
    ELSE
      ROLLBACK;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `debit_withdrawal` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_withdrawal`(IN first_id VARCHAR(18), IN amount DECIMAL(10,2) )
BEGIN
  DECLARE test1,test2 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET balance=balance-amount WHERE idaccount=first_id AND balance >= amount;
  SET test1=ROW_COUNT();
    IF (test1 > 0 ) THEN   
      COMMIT;    
      INSERT INTO transaction(idaccount,action,amount,date) VALUES(first_id,'Nosto',amount,NOW());
    ELSE
      ROLLBACK;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-02-17 13:42:44
