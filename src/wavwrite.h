#ifndef WAVWRITE_H
#define	WAVWRITE_H

namespace wav {

    template <typename T>
    inline void write(std::ofstream& stream, const T& t) {
        stream.write(reinterpret_cast<const char*> (&t), sizeof (T));
    }

    template <typename T>
    inline void writeFormat(std::ofstream& stream) {
        write<int16_t>(stream, 1);
    }

    template <>
    inline void writeFormat<float>(std::ofstream& stream) {
        write<int16_t>(stream, 3);
    }

    template <typename TYPE>
    inline void writeFile(char const* outFile, std::vector<TYPE> const& data, int32_t sampleRate, int16_t numChannels) {

        std::ofstream stream(outFile, std::ios::binary);

        // RIFF header
        stream.write("RIFF", 4);
        write<int32_t>(stream, 36 + data.size() * sizeof (TYPE));
        stream.write("WAVE", 4);

        // fmt subchunk        
        stream.write("fmt ", 4);
        write<int32_t>(stream, 16);
        writeFormat<TYPE>(stream); // 1 - all types, 3 - float
        write<int16_t>(stream, numChannels); // Channels
        write<int32_t>(stream, sampleRate); // Sample Rate
        write<int32_t>(stream, sampleRate * numChannels * sizeof (TYPE)); // Byterate
        write<int16_t>(stream, numChannels * sizeof (TYPE)); // Frame size
        write<int16_t>(stream, 8 * sizeof (TYPE)); // Bits per sample

        // data
        stream.write("data", 4);
        write<int32_t>(stream, sizeof (TYPE) * data.size() * numChannels);

        for (typename std::vector<TYPE>::const_iterator it = data.begin(); it != data.end(); ++it) {
            write<TYPE>(stream, *it);
        }

        stream.close();

    }

}

#endif	/* WAVWRITE_H */

