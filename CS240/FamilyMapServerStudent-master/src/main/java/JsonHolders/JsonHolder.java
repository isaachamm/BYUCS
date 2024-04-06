package JsonHolders;

import com.google.gson.Gson;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class JsonHolder {

    private LocationData locationData;
    private Surnames surnames;
    private MaleNames maleNames;
    private FemaleNames femaleNames;

    public void fillData() throws FileNotFoundException {
        Gson gson = new Gson();

        String location = readData("json/locations.json");
        String fNames = readData("json/fnames.json");
        String mNames = readData("json/mnames.json");
        String snames = readData("json/snames.json");

        locationData = gson.fromJson(location, LocationData.class);
        femaleNames = gson.fromJson(fNames, FemaleNames.class);
        surnames = gson.fromJson(snames, Surnames.class);
        maleNames = gson.fromJson(mNames, MaleNames.class);
    }

    private String readData(String filePath) throws FileNotFoundException {
        File file = new File(filePath);

        Scanner scanner = new Scanner(file);
        StringBuilder sb = new StringBuilder();

        while(scanner.hasNext()) {
            sb.append(scanner.nextLine());
        }

        return sb.toString();
    }

    private String[] parseData(String filePath) throws FileNotFoundException {
        File file = new File(filePath);

        Scanner scanner = new Scanner(file);
        scanner.useDelimiter("\"");
        StringBuilder sb = new StringBuilder();
        List<String> list = new ArrayList<>();

        while(scanner.hasNext()) {
//            sb.append(scanner.next());
            list.add(scanner.next());
        }

        String[] array = new String[list.size()];
        array = list.toArray(array);

        return array;
    }

    public LocationData getLocationData() {
        return locationData;
    }

    public void setLocationData(LocationData locationData) {
        this.locationData = locationData;
    }

    public Surnames getSurnames() {
        return surnames;
    }

    public void setSurnames(Surnames surnames) {
        this.surnames = surnames;
    }

    public MaleNames getMaleNames() {
        return maleNames;
    }

    public void setMaleNames(MaleNames maleNames) {
        this.maleNames = maleNames;
    }

    public FemaleNames getFemaleNames() {
        return femaleNames;
    }

    public void setFemaleNames(FemaleNames femaleNames) {
        this.femaleNames = femaleNames;
    }
}
