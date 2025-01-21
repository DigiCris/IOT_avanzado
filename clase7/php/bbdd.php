<?php
$conexion = new mysqli("localhost", "usuario", "contraseña", "basededatos");
if ($conexion->connect_error) {
    die("Error de conexión: " . $conexion->connect_error);
}
$resultado = $conexion->query("SELECT * FROM usuarios");
while ($fila = $resultado->fetch_assoc()) {
    echo $fila['nombre'];
}
$conexion->close();
?>