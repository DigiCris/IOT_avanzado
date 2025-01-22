<?php
// Verifica si se recibió el parámetro 'led'
if (isset($_GET['led'])) {
    // Obtiene el valor de 'led'
    $ledValue = $_GET['led'];

    // Crea un arreglo con el formato requerido
    $data = array("value" => $ledValue);
    
    // Convierte el arreglo a formato JSON
    $jsonData = json_encode($data, JSON_PRETTY_PRINT);

    // Escribe el JSON en el archivo led.json
    file_put_contents('led.json', $jsonData);

    // Respuesta de éxito
    echo "El archivo led.json ha sido actualizado con el valor: " . $ledValue;
} else {
    // Respuesta si no se ha recibido el parámetro
    echo "No se ha recibido el parámetro 'led'.";
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <a href="./index.php?led=1"><button>Apagar</button></a>
    <a href="./index.php?led=0"><button>Prender</button></a>
</body>
</html>