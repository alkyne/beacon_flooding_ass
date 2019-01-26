#include <iostream>
#include <tins/tins.h>
#include <unistd.h>
#include <string>
#include <cstdlib>

using namespace Tins;

int main() {

	int cnt = 0;
	while(cnt < 5000) {
		Dot11Beacon beacon;
		// Make this a broadcast frame. Note that Dot11::BROADCAST
		// is just the same as "ff:ff:ff:ff:ff:ff"
		beacon.addr1(Dot11::BROADCAST);

		// We'll set the source address to some arbitrary address
		beacon.addr2("00:01:02:03:04:05");

		// Set the bssid, to the same one as above
		beacon.addr3(beacon.addr2());

		// Our current channel is 1~6
		int channel = (cnt % 6) + 1;
		beacon.ds_parameter_set(channel);
		// This is our list of supported rates:
		beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
		// Let's add an ssid option
		std::string e_ssid = "gilgil_is_handsome_"+std::to_string(cnt % 6);	
		beacon.ssid(e_ssid);

		// Encryption: we'll say we use WPA2-psk encryption
		beacon.rsn_information(RSNInformation::wpa2_psk());

		// interface
		NetworkInterface iface("wlx88366cf83439"); 	

		// radiotap
		RadioTap radio;
		radio.inner_pdu(beacon);

		// sender
		PacketSender sender;
		sender.send(radio, iface);


		usleep(100000/3);
		std::cout << "sent " << ++cnt << std::endl;

	}
}
