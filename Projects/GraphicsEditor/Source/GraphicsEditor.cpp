#include <GojoEngine.h>

int main()
{
    GojoEngine::Engine::StartUp();

    // Testing log system
    // Log levels
	GOJO_LOG_TRACE("GraphicsEditor", "TRACE");
	GOJO_LOG_INFO("GraphicsEditor", "INFO");
	GOJO_LOG_DEBUG("GraphicsEditor", "DEBUG");
	GOJO_LOG_WARNING("GraphicsEditor", "WARNING");
	GOJO_LOG_ERROR("GraphicsEditor", "ERROR");
	GOJO_LOG_FATAL("GraphicsEditor", "FATAL");

    // GOJO_ASSERT(1 == 0);                                 PASSED
    // GOJO_ASSERT_MESSAGE(1 == 0, "Bro 1 != 0 wtf");       PASSED
    // GOJO_ASSERT_DEBUG(1 == 0);                           PASSED

    GojoEngine::Engine::ShutDown();

    return 0;
}