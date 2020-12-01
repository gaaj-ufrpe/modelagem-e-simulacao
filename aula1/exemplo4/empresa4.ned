package exemplo4;

simple Maquina4 {
    parameters:
        @display("i=device/laptop;i2=status/red, red");
    gates:
        inout port[2];
}

network Empresa4 {
    types:
        channel D extends ned.DelayChannel {
            delay = 60s;
        }
    submodules:
        m[3]: Maquina4;
    connections:
        for i=0..sizeof(m)-1 {
        	m[i].port[0] <--> D <--> m[(i+1)%sizeof(m)].port[1];
        }
}
