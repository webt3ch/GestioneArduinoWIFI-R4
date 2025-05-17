function aggiornaDati() {
    fetch('dati.txt')
        .then(response => response.text())
        .then(data => {
            const datiDiv = document.getElementById('dati');
            datiDiv.innerText = data;
            datiDiv.classList.add('updated');

            setTimeout(() => {
                datiDiv.classList.remove('updated');
            }, 300);
        })
        .catch(error => {
            console.error("Errore nel recupero dei dati:", error);
            document.getElementById('dati').innerText = "Errore nel caricamento";
        });
}

aggiornaDati();
setInterval(aggiornaDati, 1000);
