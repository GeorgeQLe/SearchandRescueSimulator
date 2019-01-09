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

    enum class enNeuronErrorTypes {
        all_clear,
        current_layer,
        node_id,
        neuron_targets,
        no_inputs,
        no_weights,
        count
    };

    struct NeuronError {
        NeuronError() { }
        NeuronError(enNeuronErrorTypes code);
        NeuronError(enNeuronErrorTypes code, const std::string& error_message) : m_error_code(code), m_error_message(error_message) { }
        enNeuronErrorTypes m_error_code = enNeuronErrorTypes::all_clear;
        std::string m_error_message = "No error";
    };

    struct NeuronIntegrityCheckResult {
        NeuronIntegrityCheckResult() : m_error(enNeuronErrorTypes::all_clear) { }
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

        bool operator==(const NeuronTargets& right) const {
            if(right.m_target_coords == this->m_target_coords) {
                return true;
            }
            return false;
        }

        NeuronTargets operator=(const NeuronTargets& right) {
            if(right == *this) {
                return *this;
            }

            this->m_target_coords = right.m_target_coords;

            return *this;
        }

        std::shared_ptr<std::map<unsigned, std::vector<unsigned>>> m_target_coords = nullptr;
    };

    template<typename T>
    struct NeuronReturnValue {
        NeuronReturnValue(T value, const NeuronTargets& targets) : m_return_value(value, targets) {}
        NeuronReturnValue(const NeuronError& error_information) : m_potential_error(error_information.m_error_code, error_information.m_error_message) { } 

        NeuronError m_potential_error;
        std::pair<T, NeuronTargets> m_return_value;
    };

    struct NeuronSettings {
        NeuronSettings() { }
        NeuronSettings(unsigned current_layer, unsigned node_id) : m_current_layer(current_layer), m_node_id(node_id) { }

        bool operator==(const NeuronSettings& right) const {
            if((right.m_current_layer == this->m_node_id) && (right.m_node_id == this->m_node_id)) {
                return true;
            }
            return false;
        }

        NeuronSettings operator=(const NeuronSettings& right) {
            this->m_current_layer = right.m_current_layer;
            this->m_node_id = right.m_node_id;
            return *this;
        }

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

        bool operator==(const NeuronWeightValue& right) const {
            if(right.m_weight_value == this->m_weight_value) {
                return true;
            }
            return false;
        }
        
        NeuronWeightValue operator=(const NeuronWeightValue& right) {
            if(right == *this) {
                return *this;
            }

            this->m_weight_value = right.m_weight_value;

            return *this;
        }

        std::shared_ptr<std::pair<bool, double>> m_weight_value;
    };

    template<typename T>
    class Neuron {
        using NeuronInputs = std::shared_ptr<std::vector<T>>;
        public:
        Neuron() { }
        Neuron(const Neuron<T>& neuron) : m_input_values(neuron.m_input_values), m_components(neuron.m_components), m_target_neurons(neuron.m_target_neurons), m_weight(neuron.m_weight) { }

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
        void add_neuron_inputs(const std::vector<T>& input_values);

        // debug function
        // checks to make sure the neuron is properly setup
        NeuronIntegrityCheckResult ensure_neuron_integrity();

        /*----------------------------------------------------------------------------------------
            This function evaluates the neuron based on the input values 
        ----------------------------------------------------------------------------------------*/
        NeuronReturnValue<T> evaluate();

        /*----------------------------------------------------------------------------------------
            This function is for the input layer neurons, who do not initially have input values.
            The input into this function is a vector of either boolean or double values.
        ----------------------------------------------------------------------------------------*/
        NeuronReturnValue<T> evaluate(const std::vector<T>& input_values);

        bool operator==(const Neuron& right) const {
            if((right.m_input_values_bool == this->m_input_values_bool) && (right.m_input_values_double == this->m_input_values_double) &&
                (right.m_components == this->m_components) && (right.m_target_neurons == this->m_target_neurons) && (right.m_weight == this->m_weight)) {
                    return true;
                }
            return false;
        }

        Neuron operator=(const Neuron& right) {
            if(right == *this) {
                return *this;
            }

            this->m_input_values = right.m_input_values;
        }

        private:
        NeuronInputs m_input_values = nullptr;
        NeuronSettings m_components;
        NeuronTargets m_target_neurons;
        NeuronWeightValue m_weight;
    };
}

#include "NeuralNetwork/implementation/Neuron.imp"

#endif