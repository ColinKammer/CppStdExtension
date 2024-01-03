#pragma once

#include <vector>
#include <tuple>
#include <stdexcept>
#include <optional>
#include <utility>


namespace cjk {
	template< typename KeyT, typename ValT>
	class FlatMap {
		std::vector<KeyT> m_keys;
		std::vector<ValT> m_values;

		std::optional<size_t> getKeyIndex(const KeyT& key) const {
			return first_index_if(m_keys, [&](const auto& k) {return k == key; });
		}

	public:
		bool insert(KeyT&& key, ValT&& val) {
			if (getKeyIndex(key)) return false;
			m_keys.emplace_back(std::forward<KeyT>(key));
			m_values.emplace_back(std::forward<ValT>(val));
			return true;
		}
		bool insert(const KeyT& key, const ValT& val) {
			if (getKeyIndex(key)) return false;
			m_keys.push_back(key);
			m_values.push_back(val);
			return true;
		}

		ValT& at(const KeyT& key) {
			const auto f = getKeyIndex(key);
			if (!f) throw std::out_of_range("Key not found");
			return m_values[f.value()];
		}
		const ValT& at(const KeyT& key) const {
			const auto f = getKeyIndex(key);
			if (!f) throw std::out_of_range("Key not found");
			return m_values[f.value()];
		}

		const ValT* at_orNull(const KeyT& key) const {
			const auto f = getKeyIndex(key);
			if (!f) return nullptr;
			size_t index = f.value();
			return &m_values[index];
		}

		size_t size() const {
			return m_keys.size();
		}

		const std::vector<KeyT>& keys() const { return m_keys; };

	};

}
