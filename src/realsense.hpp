#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/variant/packed_byte_array.hpp>

#include <librealsense2/rs.hpp>

using namespace godot;

class RealSense : public Object
{
	GDCLASS(RealSense, Object);

	static RealSense *singleton;

	rs2::context context;
	rs2::pipeline pipe;

	PackedByteArray colour_image_data;
	PackedByteArray depth_image_data;

protected:
	static void _bind_methods();

public:
	static RealSense *get_singleton();

	RealSense();
	~RealSense();

	bool poll_frame();
	void open();
	void close();
	PackedByteArray get_colour_image();
	PackedByteArray get_depth_image();
};
