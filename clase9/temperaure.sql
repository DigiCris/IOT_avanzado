-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 29-01-2025 a las 21:40:45
-- Versión del servidor: 10.6.20-MariaDB-cll-lve
-- Versión de PHP: 8.1.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `comunytc_test`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `temperaure`
--

CREATE TABLE `temperaure` (
  `id` int(10) UNSIGNED NOT NULL COMMENT 'identificador de medicion',
  `date` datetime NOT NULL DEFAULT current_timestamp() COMMENT 'timestamp de med.',
  `temp` int(11) NOT NULL COMMENT 'medicion de temp.'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Volcado de datos para la tabla `temperaure`
--

INSERT INTO `temperaure` (`id`, `date`, `temp`) VALUES
(1, '2025-01-29 20:45:37', 30);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `temperaure`
--
ALTER TABLE `temperaure`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `temperaure`
--
ALTER TABLE `temperaure`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'identificador de medicion', AUTO_INCREMENT=33;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
