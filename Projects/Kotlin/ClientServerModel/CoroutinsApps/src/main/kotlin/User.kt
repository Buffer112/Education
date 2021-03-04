import kotlin.*

class User(ip : Int, timeSleep : Long) : Client(ip, timeSleep) {

    override fun body() {
        println("I am user ${ip}")
        Internet.sandMsg(Massage(100, this.ip, "Hello Server"))
    }

    override fun getMsg(msg: Massage) {
        print("User get msg: ")
        super.getMsg(msg)
    }
}