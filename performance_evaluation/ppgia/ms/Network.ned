package ppgia.ms;

network Network {
    parameters:
        int nclients = default(10);
    submodules:
        client[nclients]: Client;
        cloud: Cloud;
    connections:
        //As conex�es s� podem ser feitas na mesma hierarquia.
        //N�o � poss�vel conectar de client para um submodulo de cloud
        for i=0..(nclients-1) {
        	client[i].out --> Ethernet100 --> cloud.in++;
        }
}
