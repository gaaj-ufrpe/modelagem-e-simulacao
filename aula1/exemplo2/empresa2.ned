package exemplo2;

simple Maquina2
{
    parameters:
        @display("i=device/pc2");
    gates:
        input in;
        output out;
}

network Empresa2
{
    submodules:
        m1: Maquina2 {
            parameters:
                @display("i=,red");                
        };
        m2: Maquina2 {
            parameters:
                @display("i=,red");                
        };
        m3: Maquina2 {
            parameters:
                @display("i=,red");                
        };
    connections:
        m1.out --> {delay = 60s;} --> m2.in;
        m2.out --> {delay = 60s;} --> m3.in;
        m3.out --> {delay = 60s;} --> m1.in;
}