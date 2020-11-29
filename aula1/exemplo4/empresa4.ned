package exemplo4;

simple Maquina4 
{
    parameters:
        @display("i=device/laptop;i2=status/red, red");
    gates:
        inout port1;
        inout port2;
}

network Empresa4
{
    submodules:
        m1: Maquina4;
        m2: Maquina4;
        m3: Maquina4;
    connections:
        m1.port1 <--> {  delay = 60s; } <--> m2.port2;
        m2.port1 <--> {  delay = 60s; } <--> m3.port2;
        m3.port1 <--> {  delay = 60s; } <--> m1.port2;
}
