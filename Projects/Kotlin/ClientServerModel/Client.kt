import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlin.coroutines.CoroutineContext

abstract class Client(ip: Int, timeSleep : Long) {
    protected var ip = -1
    var live = true
    protected var timeSleep = 1000L
    private val encryptor = AESEncryptorGCM()
    protected fun ecryptMsg(msg : String, key : String) : String? {
        return encryptor.encrypt(msg, key)
    }
    protected fun decryptMsg(msg : String, key : String) : String? {
        return encryptor.decryptWithAES(key, msg)
    }
    init{

        this.ip = ip
        this.timeSleep = timeSleep
    }
    fun kill() {
        live = false
    }
    abstract fun body()
    suspend fun Threads(context : CoroutineContext){
        CoroutineScope(context).launch {
            while (live)
            {
                delay(timeSleep)
                body()
            }
        }
    }
    fun sandMsg(msg : Massage){
        Internet.sandMsg(msg)
    }
    open fun getMsg(msg : Massage){
        println("I ${ip} got msg ${msg.msg} from ${msg.ipSender} ")
    }
}