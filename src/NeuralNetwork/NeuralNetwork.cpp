/*  Copyright 2018 George Le

*/
#include <iostream> // std::cout

#include "NeuralNetwork/NeuralNetwork.hpp"

nsNeuralNetwork::NeuralNetworkLayerConstructionResult nsNeuralNetwork::NeuralNetwork::add_new_layer(unsigned layer_index, const nsNeuralNetwork::NeuralNetworkLayer& new_layer_of_neurons) {
    // checks to make sure that the passed index is within the bounds of the neural network
    if(layer_index < this->m_neural_network_information.m_num_of_layers) {
        // determines if the passed index of the new layer is already in the neural network
        auto it = this->m_neural_network_layers.m_neurons.find(layer_index);
        if(it != this->m_neural_network_layers.m_neurons.end()) {
            // adds the neuron layer to the neural network and sets the values for the neurons in the layer
            this->m_neural_network_layers.m_neurons[layer_index] = new_layer_of_neurons;
            for(unsigned i = 0; i < this->m_neural_network_layers.m_neurons[layer_index].size(); ++i) {
                this->m_neural_network_layers.m_neurons[layer_index].at(i).set_layer(layer_index);
                this->m_neural_network_layers.m_neurons[layer_index].at(i).set_node_id(i + 1);
            }

            // this is for the input layer
            if(layer_index == 0) {
                this->connecting_to_next_layer(layer_index);
            }
            // this is for all other layers
            else {
                this->connecting_to_prev_layer(layer_index);
            }
        }
        else {
            return { "Error: A layer already exists at the specified index:" + std::to_string(layer_index) + ".\n" };
        }
    }
    else {
        return {"Error: The layer index specified is beyond the size of the neural network.:" + std::to_string(layer_index) + "/" + std::to_string(this->m_neural_network_information.m_num_of_layers) + ".\n"};
    }
    return {};
}

nsNeuralNetwork::NeuralNetworkLayerConstructionResult nsNeuralNetwork::NeuralNetwork::overwrite_layer(unsigned layer_index, const nsNeuralNetwork::NeuralNetworkLayer& replacement_layer_of_neurons) {
    if(layer_index >= this->m_neural_network_information.m_num_of_layers) {
        return {"Error: The layer does not connect to the rest of the neural network."};
    }
    
    // naive insertion or replacement of the layer of neurons at the passed index location
    this->m_neural_network_layers.m_neurons[layer_index] = replacement_layer_of_neurons;

    return {};
}

bool nsNeuralNetwork::NeuralNetwork::connecting_to_prev_layer(unsigned current_layer_index) {
    if(current_layer_index == 0 || current_layer_index >= this->m_neural_network_information.m_num_of_layers) {
        return false;
    }
    else {
        for(unsigned i = 0; i < this->m_neural_network_layers.m_neurons.at(current_layer_index - 1).size(); ++i) {
            this->m_neural_network_layers.m_neurons.at(current_layer_index - 1).at(i).set_layer(current_layer_index - 1);
            this->m_neural_network_layers.m_neurons.at(current_layer_index - 1).at(i).set_node_id(i);
            for(unsigned j = 0; j < this->m_neural_network_layers.m_neurons.at(current_layer_index).size(); ++j) {
                this->m_neural_network_layers.m_neurons.at(current_layer_index - 1).at(i).add_target_neuron(current_layer_index, j);
            }
        }
    }
    return true;
}

bool nsNeuralNetwork::NeuralNetwork::connecting_to_next_layer(unsigned int current_layer_index) {
    if(current_layer_index >= this->m_neural_network_information.m_num_of_layers - 1) {
        return false;   
    }
    else {
        for(unsigned i = 0; i < this->m_neural_network_layers.m_neurons[current_layer_index].size(); ++i) {
            this->m_neural_network_layers.m_neurons.at(current_layer_index).at(i).set_layer(current_layer_index + 1);
            this->m_neural_network_layers.m_neurons.at(current_layer_index).at(i).set_node_id(i);
            for(unsigned int j = 0; j < this->m_neural_network_layers.m_neurons.at(current_layer_index + 1).size(); ++j) {
                this->m_neural_network_layers.m_neurons.at(current_layer_index).at(i).add_target_neuron(current_layer_index + 1, j);
            }
        }
    }
    return true;
}

bool nsNeuralNetwork::NeuralNetwork::verify_connections() {
    for(unsigned i = 0; i < this->m_neural_network_information.m_num_of_layers; ++i) {
        for(unsigned j = 0; j < this->m_neural_network_layers.m_neurons.size(); ++j) {
            if(!this->m_neural_network_layers.m_neurons.at(i).at(j).ensure_neuron_integrity().m_has_error) {
                return false;
            }
            else if(this->m_neural_network_layers.m_neurons.at(i).size() == 0) {
                return false;
            }
        }
    }
    return true;
}

nsNeuralNetwork::NeuralNetworkReturnDouble nsNeuralNetwork::NeuralNetwork::evaluate_double(const std::vector<double>& input_values) {
    if(!this->verify_connections()) {
        return { true, "Neural Network error: Connctions error" };
    }
    if(input_values.size() != this->m_neural_network_layers.m_neurons.at(0).size()) {
        return { true, "There are not enough inputs for the neural network. Either fix the number of inputs or change the number of input layer neurons." };
    }
    if(this->m_neural_network_layers.m_neurons.at(this->m_neural_network_layers.m_neurons.size() - 1).size() != 1) {
        return { true, "There is more than 1 output layer neuron." };
    }

    // 
    double f_node_value = 0.0;
    for(unsigned i = 0; i < this->m_neural_network_information.m_num_of_layers; ++i) {
        // for all hidden layers
        if(i != 0) {
            std::vector<double> f_neuron_output_values;
            // collects all of the output values of the previous laver
            for(unsigned j = 0; j < this->m_neural_network_layers.m_neurons.at(i).size(); ++j) {
                f_neuron_output_values.push_back(this->m_neural_network_layers.m_neurons.at(i - 1).at(j).evaluate().m_return_value_double.first);
            }
            // evaluates the current output values of the current_layer
            for(unsigned j = 0; j < this->m_neural_network_layers.m_neurons.at(i).size(); ++j) {
                this->m_neural_network_layers.m_neurons.at(i).at(j).add_neuron_inputs_double(f_neuron_output_values);
            }
        }
        // for the input layer
        else if(i == 0) {
            for(unsigned j = 0; j < this->m_neural_network_layers.m_neurons.at(i).size(); ++j) {
                this->m_neural_network_layers.m_neurons.at(i).at(j).add_neuron_inputs_double({input_values.at(j)});
            }
        }
        // for the output layer
        else if(i == (this->m_neural_network_information.m_num_of_layers - 1)) {
            std::vector<double> f_neuron_output_values;
            // collects all of the output values of the previous laver
            for(unsigned int j = 0; j < this->m_neural_network_layers.m_neurons.at(i).size(); ++j) {
                f_neuron_output_values.push_back(this->m_neural_network_layers.m_neurons.at(i - 1).at(j).evaluate().m_return_value_double.first);
            }
            // evaluates the current output values of the current_layer
            for(unsigned int j = 0; j < this->m_neural_network_layers.m_neurons.at(i).size(); ++j) {
                this->m_neural_network_layers.m_neurons.at(i).at(j).add_neuron_inputs_double(f_neuron_output_values);
            }
            f_node_value = this->m_neural_network_layers.m_neurons.at(this->m_neural_network_layers.m_neurons.size() - 1).at(0).evaluate().m_return_value_double.first;
        }
    }
    return { f_node_value };
}

nsNeuralNetwork::NeuralNetworkReturnBool nsNeuralNetwork::NeuralNetwork::evaluate_bool(const std::vector<bool>& input_values) {
    if(!this->verify_connections()) {
        return { true, "Neural Network error: Connctions error" };
    }
    if(input_values.size() != this->m_neural_network_layers.m_neurons.at(0).size()) {
        return { true, "There are not enough inputs for the neural network. Either fix the number of inputs or change the number of input layer neurons." };
    }
    if(this->m_neural_network_layers.m_neurons.at(this->m_neural_network_layers.m_neurons.size() - 1).size() != 1) {
        return { true, "There is more than 1 output layer neuron." };
    }

    for(unsigned int i = 0; i < this->m_neural_network_information.m_num_of_layers; ++i) {
        // TODO
    }
    return false;
}

nsNeuralNetwork::NeuralNetworkReturnBool nsNeuralNetwork::NeuralNetwork::evaluate_bool(const std::vector<double>& input_values, double radix_point) {
    if(!this->verify_connections()) {
        return { true, "Neural Network error: Connctions error" };
    }
    if(input_values.size() != this->m_neural_network_layers.m_neurons.at(0).size()) {
        return { true, "There are not enough inputs for the neural network. Either fix the number of inputs or change the number of input layer neurons." };
    }
    if(this->m_neural_network_layers.m_neurons.at(this->m_neural_network_layers.m_neurons.size() - 1).size() != 1) {
        return { true, "There is more than 1 output layer neuron." };
    }

    for(unsigned int i = 0; i < this->m_neural_network_information.m_num_of_layers; ++i) {
        // TODO
    }
    return false;
}