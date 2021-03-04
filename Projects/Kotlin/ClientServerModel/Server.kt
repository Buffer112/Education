
import kotlin.*
object Server : Client(100, 1000L) {
    fun getIpp() : Int{
        return this.ip
    }
    override fun body() {
        println("I am server ${ip}")
    }
    override fun getMsg(msg: Massage) {
        print("Server get msg: ")
        super.getMsg(msg)
    }
}