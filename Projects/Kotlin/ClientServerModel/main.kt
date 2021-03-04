import kotlinx.coroutines.*
import java.util.*
import kotlin.*
import kotlin.coroutines.CoroutineContext
import kotlin.coroutines.EmptyCoroutineContext

suspend fun main() = coroutineScope {
    Internet.init(coroutineContext)
    Internet.addClient(1000L)
    Internet.addClient(1000L)
    Internet.addClient(1000L)
}