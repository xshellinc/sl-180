import UIKit

class ViewController: UIViewController {
    var simpleBluetoothIO: SimpleBluetoothIO!


    @IBOutlet weak var brightnessValue: UILabel!
    @IBOutlet weak var slider: UISlider!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        simpleBluetoothIO = SimpleBluetoothIO(serviceUUID: "19B10000-E8F2-537E-4F6C-D104768A1214", delegate: self)
        
    }

    @IBAction func sliderChange(_ sender: UISlider) {
        var myIntValue = Int8(slider.value)
        print(myIntValue.description)
        simpleBluetoothIO.writeValue(value: myIntValue)
        brightnessValue.text = myIntValue.description
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
