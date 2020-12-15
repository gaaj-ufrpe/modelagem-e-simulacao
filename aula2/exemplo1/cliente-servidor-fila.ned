package exemplo1;

simple ServidorFila {
    parameters:
        @display("i=device/mainframe");
        int capacidadeFila = default(0);
        double tempoProcessamento = default(1.0);
        gates:
        input in;
}

network RedeFila {
    types:
        channel Ethernet100 extends ned.DatarateChannel {
            delay = 0.5s;
        }
    submodules:
        cliente: Cliente;
        servidor: ServidorFila;
    connections:
        cliente.out --> Ethernet100 --> servidor.in;
}
