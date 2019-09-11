/*
 * Copyright (c) 2019 Föreningen Sambruk
 *
 * You should have received a copy of the MIT license along with this project.
 * If not, see <https://opensource.org/licenses/MIT>.
 */

#include <iostream>
#include <curl/curl.h>
#include <boost/program_options.hpp>
#include "fedtlsauth/metadata_parser.hpp"

namespace auth = federated_tls_auth;
namespace po = boost::program_options;

void http_get(const auth::server_connection_info & server,
              const std::string& suffix_path,
              const std::string& cert_path,
              const std::string& key_path) {
    CURL* curl = curl_easy_init();

    if (curl) {
        // Set URL = base URL from metadata plus path given on command line
        auto full_url = server.end_points[0].url + "/" + suffix_path;
        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());

        // Set our client certificate
        curl_easy_setopt(curl, CURLOPT_SSLCERT, cert_path.c_str());

        // Set our private key
        curl_easy_setopt(curl, CURLOPT_SSLKEY, key_path.c_str());

        // Set CA store from metadata
        curl_easy_setopt(curl, CURLOPT_CAINFO, server.castore->get_path().c_str());
        
        // Set pinned public key
        auto combined_pins = auth::concatenate_keys(server.end_points[0].pins);
        curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, combined_pins.c_str());
        
        // Do the actual HTTP GET
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Failed to perform GET: "
                      << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}

// Parses a tag specification (comma separated string) from the command line
std::vector<std::string> parse_tags(const std::string tag_spec) {
    std::vector<std::string> tags;
    std::istringstream ss(tag_spec);
    std::string token;

    while(std::getline(ss, token, ',')) {
        tags.push_back(token);
    }

    return tags;
}

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    std::string metadata_path, entity, server_tags, cert, key, path;
    
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("metadata", po::value<std::string>(&metadata_path)->required(), "path to metadata")
        ("entity", po::value<std::string>(&entity)->required(), "entity to connect to")
        ("server-tags", po::value<std::string>(&server_tags), "tags for servers to connect to (comma separated)")
        ("cert", po::value<std::string>(&cert)->required(), "client certificate")
        ("key", po::value<std::string>(&key)->required(), "client private key")
        ("path", po::value<std::string>(&path)->required(), "path to GET")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    try {
        po::notify(vm);

        auto connection_info =
            auth::get_server_by_tags(metadata_path, entity, parse_tags(server_tags));

        http_get(connection_info, path, cert, key);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const po::error& e) {
        std::cerr << e.what() << std::endl;
    }

    curl_global_cleanup();    
    return EXIT_SUCCESS;
}
