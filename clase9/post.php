<?php
// Configuración de la base de datos
$servername = "localhost"; // Cambia esto si tu servidor MySQL está en otro lugar
$username = "comunytc_test";
$password = "DA^Ek=0+lEGU"; // Cambia 'tu_password' por la contraseña real
$dbname = "comunytc_test";

// Crear conexión
$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

// Consulta para insertar datos
$temp_value = 21; // Valor de temperatura a insertar
$sql = "INSERT INTO temperaure (temp) VALUES ('$temp_value')";

// Ejecutar la consulta
if ($conn->query($sql) === TRUE) {
    echo "Nuevo registro creado exitosamente";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

// Cerrar conexión
$conn->close();
?>