import kotlinx.coroutines.*

suspend fun main() = coroutineScope {
    Internet.init(coroutineContext)
    Internet.addClient(1000L)
    Internet.addClient(1000L)
    Internet.addClient(1000L)
}