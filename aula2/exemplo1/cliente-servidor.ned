package exemplo1;

simple Cliente {
    parameters:
        @display("i=device/laptop");
    gates:
        output out;
}

simple Servidor {
    parameters:
        @display("i=device/mainframe");
    gates:
        input in;
}

network Rede {
    types:
        channel Ethernet100 extends ned.DatarateChannel {
            delay = 0.5s;
        }
    submodules:
        cliente: Cliente;
        servidor: Servidor;
    connections:
        cliente.out --> Ethernet100 --> servidor.in;
}
