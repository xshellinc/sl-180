import UIKit

class ViewController: UIViewController {
    var simpleBluetoothIO: SimpleBluetoothIO!


    @IBOutlet weak var brightnessValue: UILabel!
    @IBOutlet weak var slider: UISlider!
    var oldValue: Int8!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        simpleBluetoothIO = SimpleBluetoothIO(serviceUUID: "5ABF9F0B-338C-4C9F-871A-02074BB0D71D", delegate: self)
        var myIntValue = Int8(slider.value)
        print(myIntValue.description)
        simpleBluetoothIO.writeValue(value: myIntValue)
        brightnessValue.text = myIntValue.description
        oldValue = Int8(slider.value)
        print(oldValue.description)
    }

    @IBAction func sliderChange(_ sender: UISlider) {
        if(oldValue != Int8(slider.value)){
            var myIntValue = Int8(slider.value)
            print(myIntValue.description)
            simpleBluetoothIO.writeValue(value: myIntValue)
            brightnessValue.text = myIntValue.description
            oldValue = Int8(slider.value)
        }
    }

}

extension ViewController: SimpleBluetoothIODelegate {
    func simpleBluetoothIO(simpleBluetoothIO: SimpleBluetoothIO, didReceiveValue value: Int8) {
        if value > 0 {
            print("ff")
            //view.backgroundColor = UIColor.yellow
        } else {
            print("ff")
            //view.backgroundColor = UIColor.black
        }
    }
}
