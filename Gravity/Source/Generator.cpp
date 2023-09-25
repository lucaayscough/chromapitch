#include "Headers.h"
#include <chrono>


//------------------------------------------------------------//
// Constructors and destructors.

Generator::Generator(){

    m_GeneratorModule = torch::jit::load(Variables::getGeneratorModulePath());
    m_MapperModule = torch::jit::load(Variables::getMapperModulePath());
    
    m_MapperModule.to(torch::kCPU);
    m_GeneratorModule.to(torch::kCPU);
    
    m_MapperModule.eval();
    m_GeneratorModule.eval();
    
}

Generator::~Generator(){}

at::Tensor Generator::generateLatents(std::int64_t seed){
    auto start = std::chrono::high_resolution_clock::now();

    torch::NoGradGuard no_grad;
    torch::manual_seed((std::uint64_t)seed);

    // Create random input tensor.
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(torch::randn({1, 512}).to(torch::kCPU));

    // Forward input to module.
    at::Tensor output = m_MapperModule.forward(inputs).toTensor();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    //Logger::writeToLog("Mapper network time: " + std::to_string(elapsed.count()));

    return output;
}

juce::var Generator::generateSample(at::Tensor& latents){
    auto start = std::chrono::high_resolution_clock::now();

    torch::NoGradGuard no_grad;

    // Create input tensor with latents.
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(latents);

    // Forward input to module.
    at::Tensor output = m_GeneratorModule.forward(inputs).toTensor();

    juce::var sample;
    sample.resize(AudioContainer::M_NUM_SAMPLES);

    float* data =  output.contiguous().data_ptr<float>();

    // Copy tensor to array.
    for(int i = 0; i < AudioContainer::M_NUM_SAMPLES; i++){
        sample[i] = data[i];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    //Logger::writeToLog("Synthesis network time: " + std::to_string(elapsed.count()));

    return sample;
}
