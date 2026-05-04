# NS3 WiFi Topology Simulation

Simple WiFi topology using ns3 with 5 nodes.

## Network Setup
- 4 UDP Clients (Nodes 0-3)
- 1 UDP Server (Node 4)
- Protocol: WiFi AdHoc 802.11b
- Packets: 20 packets sent

## Simulation Output
Creating 5 nodes...
Setting up WiFi...
Setting up Mobility...
Installing Internet Stack...
Node 0 IP: 10.1.1.1
Node 1 IP: 10.1.1.2
Node 2 IP: 10.1.1.3
Node 3 IP: 10.1.1.4
Node 4 IP: 10.1.1.5
Setting up UDP Server on Node 4...
Setting up UDP Clients on Nodes 0,1,2,3...
Running Simulation...
Simulation Done! 20 packets sent to Node 4
## How to Run
```bash
NS_LOG=SimpleWifiTopology=info ./ns3 run simple
```
