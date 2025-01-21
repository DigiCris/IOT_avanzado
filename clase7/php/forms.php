<form method="post" action="procesar.php">
    Nombre: <input type="text" name="nombre">
    <input type="submit">
</form>


<?php
// en procesar.php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nombre = $_POST['nombre'];
    echo "Hola, $nombre!";
}
?>