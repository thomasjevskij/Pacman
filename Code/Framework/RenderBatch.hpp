#ifndef RENDER_BATCH_HPP
#define RENDER_BATCH_HPP

namespace Framework
{
	// Defines the interface sent to all objects that need to draw anything.
	class DrawInterface
	{
	public:

	};

	// Defines a batch of objects to be sorted and drawn.
	class RenderBatch
	{
	public:
		void Begin();
		void End();
	private:

	};
}

#endif