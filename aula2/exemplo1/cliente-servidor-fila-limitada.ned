package exemplo1;

network RedeFilaLimitada {
    types:
        channel Ethernet100 extends ned.DatarateChannel {
            delay = 0.5s;
        }
    submodules:
        cliente: Cliente;
        servidor: ServidorFila {
            capacidadeFila = 5;
        };
    connections:
        cliente.out --> Ethernet100 --> servidor.in;
}
