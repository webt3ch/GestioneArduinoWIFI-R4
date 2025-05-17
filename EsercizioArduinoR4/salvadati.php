<?php
// Verifica se sono stati inviati i parametri 'temp' e 'humidity'
if (isset($_GET['temp']) && isset($_GET['humidity'])) {
    $temperature = $_GET['temp'];
    $humidity = $_GET['humidity'];

    // Salva i dati in un file di testo (ad esempio, 'dati.txt')
    $file = fopen("dati.txt", "a");
    if ($file) {
        $data = "Temperature: $temperature °C, Humidity: $humidity % - " . date("Y-m-d H:i:s") . "\n";
        fwrite($file, $data);
        fclose($file);
        echo "Dati salvati con successo!";
    } else {
        echo "Errore nel salvataggio dei dati!";
    }
} else {
    echo "Parametri mancanti!";
}
?>
