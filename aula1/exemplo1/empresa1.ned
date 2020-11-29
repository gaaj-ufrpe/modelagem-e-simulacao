package exemplo1;

simple Maquina1
{
    parameters:
        @display("i=device/laptop");
    gates:
        input in;
        output out;
}

network Empresa1
{
    submodules:
        m1: Maquina1;
        m2: Maquina1;
        m3: Maquina1;
    connections:
        m1.out --> {delay = 60s;} --> m2.in;
        m2.out --> {delay = 60s;} --> m3.in;
        m3.out --> {delay = 60s;} --> m1.in;
}


