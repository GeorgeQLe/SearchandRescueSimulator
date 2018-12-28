/*  Copyright 2018 George Le

    This file provides the definition for the class constructor for the NeuronError struct
    and some of the member functions of the Neuron class
*/
#include "NeuralNetwork/Neuron.hpp"

nsNeuron::NeuronError::NeuronError(enNEURON_ERROR_CODES code) : m_error_code(code) {
    if(code == enNEURON_ERROR_CODES::CURRENT_LAYER) {
        this->m_error_message = "The current layer is not yet set.";
    }
    else if(code == enNEURON_ERROR_CODES::NEURON_TARGETS) {
        this->m_error_message = "There is no target neurons set yet?";
    }
    else if(code == enNEURON_ERROR_CODES::NODE_ID) {
        this->m_error_message = "There is no set neuron id";
    }
    else if(code == enNEURON_ERROR_CODES::NO_INPUTS) {
        this->m_error_message = "There are no input to the neuron.";
    }
    else if(code == enNEURON_ERROR_CODES::NO_WEIGHTS) {
        this->m_error_message = "The neuron weight has not been set yet.";
    }
}

void nsNeuron::Neuron::add_target_neuron(unsigned target_layer_index, unsigned target_node_id) {
    // checks to see if the map of coordinates to target neurons exists and if not then build it
    if(this->m_target_neurons.m_target_coords == nullptr) {
        this->m_target_neurons.m_target_coords = std::shared_ptr<std::map<unsigned, std::vector<unsigned>>>(new std::map<unsigned, std::vector<unsigned>>);
    }
    // determines if the map 
    auto it = this->m_target_neurons.m_target_coords->find(target_layer_index);
    if(it != this->m_target_neurons.m_target_coords->end()) {
        this->m_target_neurons.m_target_coords->at(target_layer_index).push_back(target_node_id);
    }
    else {
        (*this->m_target_neurons.m_target_coords)[target_layer_index].push_back(target_node_id);
    }
}

void nsNeuron::Neuron::add_neuron_inputs_bool(const std::vector<bool>& input_values) {

}

void nsNeuron::Neuron::add_neuron_inputs_double(const std::vector<double>& input_values) { 
    this->m_input_values_double = std::shared_ptr<std::vector<double>>(new std::vector<double>(input_values));
}

nsNeuron::NeuronIntegrityCheckResult nsNeuron::Neuron::ensure_neuron_integrity() {
    if(this->m_components.m_current_layer == 0) {
        return { enNEURON_ERROR_CODES::CURRENT_LAYER };
    }
    else if(this->m_components.m_node_id == 0) {
        return { enNEURON_ERROR_CODES::NODE_ID };
    }
    else if(this->m_target_neurons.m_target_coords == nullptr) {
        return { enNEURON_ERROR_CODES::NEURON_TARGETS };
    }
    else if(this->m_weight.m_weight_value->first == false) {
        return { enNEURON_ERROR_CODES::NO_WEIGHTS };
    }
    return { };
}

nsNeuron::NeuronReturnValue nsNeuron::Neuron::evaluate() {
    if(!ensure_neuron_integrity().m_has_error) {
        enNEURON_ERROR_CODES code = ensure_neuron_integrity().m_error.m_error_code;
        return { NeuronError(code, "Cannot evaluate the neuron, it has not been properly set up") }; 
    } 
    
    if(this->m_input_values_bool) {
        bool input_value = false;
        for(unsigned i = 0; i < this->m_input_values_bool->size(); ++i) {
            if(i == 0) {
                input_value = this->m_input_values_bool->at(i);
            }
            else {
                input_value = input_value && this->m_input_values_bool->at(i); 
            }
            return { input_value, m_target_neurons };
        }
    }
    else if(this->m_input_values_double != nullptr) {
        // sum up all the input_values into a neuron
        double input_value = 0.0;
        for(unsigned i = 0; i < this->m_input_values_double->size(); ++i) {
            input_value += this->m_input_values_double->at(i);
        }
        return { input_value * m_weight.m_weight_value->second, m_target_neurons };
    }
    
    return { NeuronError(enNEURON_ERROR_CODES::NO_INPUTS) };
}

// for the input layer neurons, who do not initially have input values
nsNeuron::NeuronReturnValue nsNeuron::Neuron::evaluate(const std::vector<double>& input_values) { 
    if(!ensure_neuron_integrity().m_has_error) {
        enNEURON_ERROR_CODES code = ensure_neuron_integrity().m_error.m_error_code;
        return { NeuronError(code, "Cannot evaluate the neuron, it has not been properly set up") }; 
    } 
    
    // sum up all the input_values into a neuron
    double input_value = 0.0;
    for(unsigned i = 0; i < input_values.size(); ++i) {
        input_value += input_values.at(i);
    }

    return { input_value * m_weight.m_weight_value->second, m_target_neurons };
}