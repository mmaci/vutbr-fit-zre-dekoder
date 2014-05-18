

#include <string>
#include <cstdint>
#include <fstream>
#include <vector>

#include "decoder.h"
#include "wavwrite.h"

void processParams(int argc, char* argv[], std::string& codebookFilename, std::string& gainFilename, std::string& inFilename, std::string& outFilename) {
    if (argc != 5) {
        std::cout << "Usage: zre_proj1_linux cb_lpc.txt cb_gain.txt in.cod out.wav" << std::endl;
        return;
    }

    codebookFilename = argv[1];
    gainFilename = argv[2];
    inFilename = argv[3];
    outFilename = argv[4];
}

int main(int argc, char* argv[]) {

    std::string codebookFilename, gainCodebookFilename, inFilename, outFilename;
    std::vector<int16_t> sound;

    try {
        processParams(argc, argv, codebookFilename, gainCodebookFilename, inFilename, outFilename);
        Decoder decoder;
        decoder.loadFiles(codebookFilename, gainCodebookFilename, inFilename);
        decoder.decode();
        sound = decoder.synthesize();
        wav::writeFile(outFilename.c_str(), sound, 8000, 1);
    } 
    catch (DecoderException& e) 
    {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
    