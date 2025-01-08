import Foundation
import PaxEasyLinkControllerWrapper

public class PaxPOSLibrary {
    public static func doSomething() -> String {
        if let version = PaxEasyLinkControllerWrapper.getInstance().getVersionName(){
            return "Version: \(version)"
        }
        return ""
    }
}
