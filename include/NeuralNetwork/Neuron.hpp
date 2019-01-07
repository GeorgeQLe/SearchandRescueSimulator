/*  Copyright 2018 George Le

    This file provides the declaration of the Neuron class, which forms the basis
    for the NeuralNetwork class, and the definitions for the Neuron class's member
    functions.
*/
#ifndef NEURON_HPP
#define NEURON_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <string> // std::string
#include <utility> // std::pair
#include <vector> // std::vector

namespace nsNeuron {
    using NeuronInputsBool = std::shared_ptr<std::vector<bool>>;
    using NeuronInputsDouble = std::shared_ptr<std::vector<double>>;

    enum class enNEURON_ERROR_CODES {
        ALL_CLEAR,
        CURRENT_LAYER,
        NODE_ID,
        NEURON_TARGETS,
        NO_INPUTS,
        NO_WEIGHTS
    };

    struct NeuronError {
        NeuronError() { }
        NeuronError(enNEURON_ERROR_CODES code);
        NeuronError(enNEURON_ERROR_CODES code, const std::string& error_message) : m_error_code(code), m_error_message(error_message) { }
        enNEURON_ERROR_CODES m_error_code = enNEURON_ERROR_CODES::ALL_CLEAR;
        std::string m_error_message = "No error";
    };

    struct NeuronIntegrityCheckResult {
        NeuronIntegrityCheckResult() : m_error(enNEURON_ERROR_CODES::ALL_CLEAR) { }
        NeuronIntegrityCheckResult(const NeuronError& error) : m_has_error(true), m_error(error) { }
        bool m_has_error = false; 
        NeuronError m_error;
    };

    struct NeuronTargets {
        NeuronTargets() { }
        NeuronTargets(const NeuronTargets& targets) {
            m_target_coords = std::shared_ptr<std::map<unsigned, std::vector<unsigned>>>(new std::map<unsigned, std::vector<unsigned>>());
            if(targets.m_target_coords != nullptr) {
                *m_target_coords = *targets.m_target_coords;
            }
        }
        std::shared_ptr<std::map<unsigned, std::vector<unsigned>>> m_target_coords = nullptr;
    };

    struct NeuronReturnValue {
        NeuronReturnValue(bool value, const NeuronTargets& targets) : m_return_value_bool(value, targets) { }
        NeuronReturnValue(double value, const NeuronTargets& targets) : m_return_value_double(value, targets) { }
        NeuronReturnValue(const NeuronError& error_information) : m_potential_error(error_information.m_error_code, error_information.m_error_message) { } 

        NeuronError m_potential_error;
        std::pair<bool, NeuronTargets> m_return_value_bool;
        std::pair<double, NeuronTargets> m_return_value_double;
    };

    struct NeuronSettings {
        NeuronSettings() { }
        NeuronSettings(unsigned current_layer, unsigned node_id) : m_current_layer(current_layer), m_node_id(node_id) { }
        unsigned m_current_layer = 0;
        unsigned m_node_id = 0;
    };

    struct NeuronWeightValue {
        NeuronWeightValue() {
            m_weight_value = std::shared_ptr<std::pair<bool, double>>(new std::pair<bool, double>(false, -1.0));
        }
        NeuronWeightValue(bool has_weight) {
            m_weight_value = std::shared_ptr<std::pair<bool, double>>(new std::pair<bool, double>(false, -1.0));
        }

        std::shared_ptr<std::pair<bool, double>> m_weight_value;
    };

    class Neuron {
        public:
        Neuron() { }

        // accessor functions
        unsigned get_current_layer() const { return m_components.m_current_layer; }
        unsigned get_node_id() const { return m_components.m_node_id; }
        NeuronWeightValue get_weight() const { 
            if(!m_weight.m_weight_value->first)
            {
                return { false };
            }
            return m_weight;
        }

        // mutator functions
        void set_layer(unsigned current_layer) { m_components.m_current_layer = current_layer; }
        void set_node_id(unsigned node_id) { m_components.m_node_id = node_id; }
        void set_weight(double weight) { m_weight.m_weight_value->second = weight; m_weight.m_weight_value->first = true; } 

        void add_target_neuron(unsigned target_layer_index, unsigned target_node_id);
        void add_neuron_inputs_bool(const std::vector<bool>& input_values);
        void add_neuron_inputs_double(const std::vector<double>& input_values);

        // debug function
        // checks to make sure the neuron is properly setup
        NeuronIntegrityCheckResult ensure_neuron_integrity();

        /*----------------------------------------------------------------------------------------
            This function evaluates the neuron based on the input values 
        ----------------------------------------------------------------------------------------*/
        NeuronReturnValue evaluate();

        /*----------------------------------------------------------------------------------------
            This function is for the input layer neurons, who do not initially have input values.
            The input into this function is a vector of boolean values.
        ----------------------------------------------------------------------------------------*/
        NeuronReturnValue evaluate(const std::vector<bool>& input_values);
        
        /*----------------------------------------------------------------------------------------
            This function is for the input layer neurons, who do not initially have input values.
            The input into this function is a vector of double values.
        ----------------------------------------------------------------------------------------*/
        NeuronReturnValue evaluate(const std::vector<double>& input_values);

        private:
        NeuronInputsBool m_input_values_bool = nullptr;
        NeuronInputsDouble m_input_values_double = nullptr;
        NeuronSettings m_components;
        NeuronTargets m_target_neurons;
        NeuronWeightValue m_weight;
    };
}

#endif