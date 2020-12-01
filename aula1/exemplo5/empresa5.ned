package exemplo5;

simple Maquina5 {
    parameters:
        @display("i=device/laptop;i2=status/red, red");
    gates:
        inout port[];
}

network Empresa5 {
    types:
        channel D extends ned.DelayChannel {
            delay = 60s;
        }
    submodules:
        m[6]: Maquina5;
    connections:
        //A notação port++ inclui uma nova porta no array de portas da Máquina
        for i=0..sizeof(m)-2, for j=i+1..sizeof(m)-1 {
        	m[i].port++ <--> D <--> m[j].port++;
        }
}
