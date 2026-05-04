#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/applications-module.h"
using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("SimpleWifiTopology");
int main (int argc, char *argv[])
{
    LogComponentEnable ("SimpleWifiTopology", LOG_LEVEL_INFO);
    NS_LOG_INFO ("Creating 5 nodes...");
    NodeContainer nodes;
    nodes.Create (5);
    NS_LOG_INFO ("Setting up WiFi...");
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
    YansWifiPhyHelper phy;
    phy.SetChannel (channel.Create ());
    WifiHelper wifi;
    wifi.SetStandard (WIFI_STANDARD_80211b);
    WifiMacHelper mac;
    mac.SetType ("ns3::AdhocWifiMac");
    NetDeviceContainer devices = wifi.Install (phy, mac, nodes);
    NS_LOG_INFO ("Setting up Mobility...");
    MobilityHelper mobility;
    mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                   "MinX", DoubleValue (0.0),
                                   "MinY", DoubleValue (0.0),
                                   "DeltaX", DoubleValue (10.0),
                                   "DeltaY", DoubleValue (10.0),
                                   "GridWidth", UintegerValue (3),
                                   "LayoutType", StringValue ("RowFirst"));
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (nodes);
    NS_LOG_INFO ("Installing Internet Stack...");
    InternetStackHelper internet;
    internet.Install (nodes);
    Ipv4AddressHelper ipv4;
    ipv4.SetBase ("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = ipv4.Assign (devices);
    for (uint32_t i = 0; i < 5; i++)
      {
        NS_LOG_INFO ("Node " << i << " IP: " << interfaces.GetAddress (i));
      }
    NS_LOG_INFO ("Setting up UDP Server on Node 4...");
    uint16_t port = 9;
    UdpServerHelper server (port);
    ApplicationContainer serverApp = server.Install (nodes.Get (4));
    serverApp.Start (Seconds (1.0));
    serverApp.Stop (Seconds (10.0));
    NS_LOG_INFO ("Setting up UDP Clients on Nodes 0,1,2,3...");
    for (uint32_t i = 0; i < 4; i++)
      {
        UdpClientHelper client (interfaces.GetAddress (4), port);
        client.SetAttribute ("MaxPackets", UintegerValue (5));
        client.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
        client.SetAttribute ("PacketSize", UintegerValue (1024));
        ApplicationContainer clientApp = client.Install (nodes.Get (i));
        clientApp.Start (Seconds (2.0));
        clientApp.Stop (Seconds (10.0));
      }
    NS_LOG_INFO ("Running Simulation...");
    Simulator::Run ();
    Simulator::Destroy ();
    NS_LOG_INFO ("Simulation Done! 20 packets sent to Node 4");
    return 0;
}
