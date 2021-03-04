import kotlin.*
import kotlin.coroutines.CoroutineContext
import kotlin.coroutines.EmptyCoroutineContext

object Internet {
    var context : CoroutineContext = EmptyCoroutineContext
    private var users : List<User> = listOf()
    private var server = Server
    private var countClient = 0
    suspend fun init(context : CoroutineContext)
    {
        this.context = context
        this.server.Threads(context)
    }
    fun sandMsg(msg : Massage){
        if (msg.ipReceiver == server.getIpp())
        {
            server.getMsg(msg)
        }
        else
        {
            users[msg.ipSender].getMsg(msg)
        }
    }
    suspend fun addClient(timeDelay : Long) {
        val tempClient = User(countClient, timeDelay)
        this.users.toMutableList().add(tempClient)
        countClient += 1
        println("Client ${countClient} added!")
        tempClient.Threads(context)
    }
}