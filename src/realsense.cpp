#include "realsense.hpp"

#include <cstring>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

RealSense *RealSense::singleton = nullptr;

void RealSense::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("poll_frame"), &RealSense::poll_frame);
	ClassDB::bind_method(D_METHOD("open"), &RealSense::open);
	ClassDB::bind_method(D_METHOD("close"), &RealSense::close);
	ClassDB::bind_method(D_METHOD("get_colour_image"), &RealSense::get_colour_image);
	ClassDB::bind_method(D_METHOD("get_depth_image"), &RealSense::get_depth_image);
}

RealSense *RealSense::get_singleton()
{
	return singleton;
}

RealSense::RealSense()
{
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;

	colour_image_data.resize(1920 * 1080 * 3);
	colour_image_data.fill(0);

	depth_image_data.resize(848 * 480 * 2);
	depth_image_data.fill(0);

	UtilityFunctions::print("RealSense library initialized");
}

RealSense::~RealSense()
{
	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
	
	UtilityFunctions::print("RealSense library uninitialized");
}

void RealSense::open()
{
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 1920, 1080, RS2_FORMAT_RGB8, 30);
	cfg.enable_stream(RS2_STREAM_DEPTH, RS2_FORMAT_Z16);
	pipe.start(cfg);
}

void RealSense::close()
{
	pipe.stop();
}

bool RealSense::poll_frame()
{
	rs2::frameset frames;
	if(pipe.poll_for_frames(&frames)) {
		auto colour = frames.get_color_frame();
		memcpy(colour_image_data.begin().operator->(), colour.get_data(), colour.get_width() * colour.get_height() * colour.get_bytes_per_pixel());

		auto depth = frames.get_depth_frame();
		memcpy(depth_image_data.begin().operator->(), depth.get_data(), depth.get_width() * depth.get_height() * depth.get_bytes_per_pixel());

		return true;
	} 

	return false;
}

PackedByteArray RealSense::get_colour_image()
{
  return colour_image_data;
}

PackedByteArray RealSense::get_depth_image()
{
  return depth_image_data;
}
