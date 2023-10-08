# Machine Learning

The ideas covered in this document are based on the ideas and operating system covered in the [PROS](./pros.md) document.

## How?

The idea of using machine learning for VEX V5 robots is not new. The way that it would be implemented would likely be by first training a model using sensor data, using Tensorflow lite or Keras, and then running that model and generating inferences directly from out C++ code.

## Why it's a bad idea

The idea to use machine learning sounds great on paper. The issue is that there is not near enough flexibility in the ecosystem to allow this to function effectively.

For example, here are some of the issues that hinder this problem.

- Resource constraints - Machine learning generally takes up a large number of resources and is therefore not viable for our resource necessities.
- Lack of Accuracy - Considering that the subject in question is a language model, it would be very hard to get proper accuracy unless we take a larger model and finetune it.
- Time constraints - The amount of time that it would take to implement an idea like this pretty much outweighs the advantages it provides. We could build a better system using advanced logic gates with input sensor data.


## Alternatives
The best alternative for a program like this is to take sensor input data and compare it to a probability graph of which decision to pick, rather than a language model, which is aimed at a different type of artificial intelligence.