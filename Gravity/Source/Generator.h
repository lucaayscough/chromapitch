#pragma once


struct ReferenceCountedTensor: public juce::ReferenceCountedObject{
    ReferenceCountedTensor(at::Tensor t)
    :   tensor(t){}
    at::Tensor tensor;
    using Ptr = juce::ReferenceCountedObjectPtr<ReferenceCountedTensor>;
    at::Tensor& getTensor(){return tensor;}
};


class Generator{
public:
    torch::jit::script::Module m_GeneratorModule, m_MapperModule;

    // Constructors and destructors.
    Generator();
    ~Generator();

    at::Tensor generateLatents(std::int64_t);
    juce::var generateSample(at::Tensor&);
};
