-- --------------------------------------------------------
-- Host:                         2.139.176.212
-- Versión del servidor:         10.4.17-MariaDB - mariadb.org binary distribution
-- SO del servidor:              Win64
-- HeidiSQL Versión:             11.2.0.6213
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Volcando estructura de base de datos para bdrdelgado
CREATE DATABASE IF NOT EXISTS `bdrdelgado` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;
USE `bdrdelgado`;

-- Volcando estructura para tabla bdrdelgado.datos_sensores
CREATE TABLE IF NOT EXISTS `datos_sensores` (
  `id_dato` int(11) NOT NULL AUTO_INCREMENT,
  `id_sensor` int(11) DEFAULT NULL,
  `tipo` varchar(20) DEFAULT NULL,
  `fecha` timestamp NULL DEFAULT current_timestamp(),
  `valor` float DEFAULT NULL,
  PRIMARY KEY (`id_dato`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4;

-- Volcando datos para la tabla bdrdelgado.datos_sensores: ~8 rows (aproximadamente)
/*!40000 ALTER TABLE `datos_sensores` DISABLE KEYS */;
INSERT INTO `datos_sensores` (`id_dato`, `id_sensor`, `tipo`, `fecha`, `valor`) VALUES
	(1, 1, 'Presion atmosferica', '2021-04-22 13:05:43', 44.5),
	(2, 2, 'Temperatura', '2021-04-22 13:05:43', 21),
	(3, 3, 'Humedad', '2021-04-22 13:05:43', 32),
	(4, 4, 'Luminosidad', '2021-04-22 13:05:44', 94),
	(5, 5, 'Rayos UVA', '2021-04-22 13:05:44', 2),
	(6, 6, 'Rayos UVB', '2021-04-22 13:05:44', 1.05),
	(7, 7, 'UV Index', '2021-04-22 13:05:44', 80),
	(8, 8, 'CO2', '2021-04-22 13:05:44', 57);
/*!40000 ALTER TABLE `datos_sensores` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
