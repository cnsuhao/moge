#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>
#include <functional>
#include "meta/resource-traits.hh"
#include "meta/resource.hh"
#include "system.hh"

struct GLFWwindow;

namespace moge
{
	namespace window_detail
	{
		struct window;
	}

	using window_detail::window;


	template <>
	struct resource_traits<window> : make_resource_traits<GLFWwindow*>
	{
		// static value_type allocate();
		static void deallocate(value_type const& x);
		static void bind(value_type const& x);
	};


	namespace window_detail
	{
		struct window_events
		{
			using self = window_events;
			using uptr = std::unique_ptr<self>;

			using close_func = std::function<void ()>;
			close_func close;
		};

		struct window : resource<window>
		{
			window_events::uptr events;

			window(std::string const& title={"moge"},
					glm::ivec2 const& size ={16*60, 9*60},
					system& = system::instance());

			void vsync(bool on=true);
			void update();
		};
	}
}

