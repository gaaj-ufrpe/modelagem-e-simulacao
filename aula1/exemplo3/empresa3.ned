package exemplo3;

simple Maquina3 
{
    parameters:
        @display("i=device/laptop;i2=status/red, red");
    gates:
        input in;
        output out;
}

network Empresa3
{
    submodules:
        m1: Maquina3;
        m2: Maquina3;
        m3: Maquina3;
    connections:
        m1.out --> {  delay = 60s; } --> m2.in;
        m2.out --> {  delay = 60s; } --> m3.in;
        m3.out --> {  delay = 60s; } --> m1.in;
}
