#ifndef FIR_H
#define	FIR_H

class Fir {
    public:
        Fir() {}
        Fir(std::vector<double> const& coefficients) : _coefficients(coefficients) {}

        void setCoeffs(std::vector<double> const& coeffs) { _coefficients = coeffs; }
        std::vector<double> process(double const& gain, std::vector<double> const& input, std::vector<double>& delayed)
        {
            std::vector<double> output(input.size(), 0.0);        
            for (uint32_t i = 0; i < output.size(); i++) {

                output[i] = gain * input[i] + delayed[0];

                for (uint8_t j = 1; j < _coefficients.size(); j++) {
                    delayed[j-1] = delayed[j] - _coefficients[j] * output[i];
                }   
            }

            return output;
        }

    private:
        std::vector<double> _coefficients;

};

#endif	/* FIR_H */

