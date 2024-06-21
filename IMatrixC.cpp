#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class IMatrix {
    typedef std::vector<std::string> names;
    typedef std::vector<std::vector<int>> IntMatrix;
    typedef std::vector<int> row;
    names rnames, cnames;
    IntMatrix mt;

public:
    void readTabfile(std::string filename) {
        names rnms; // 행 이름을 저장하는 벡터
        names cnms; // 열 이름을 저장하는 벡터
        std::string line;
        row r; // 행을 나타내는 벡터
        int rownumber = 0;
        std::string scell;
        int icell;

        // 파일을 읽기 모드로 열기
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        while (std::getline(infile, line)) {
            rownumber += 1;
            std::istringstream iss(line);
            
            if (rownumber == 1) {
                iss >> scell; // 첫 번째 행의 첫 번째 열은 행 이름이므로 스킵
                while (iss >> scell) {
                    cnms.push_back(scell); // 첫 번째 행의 나머지 열은 열 이름들
                }
            } else {
                iss >> scell; // 첫 번째 열은 행 이름
                rnms.push_back(scell);

                r.clear();
                while ((iss >> icell)) {
                    r.push_back(icell); // 나머지는 정수 데이터들
                }
                mt.push_back(r); // 정수 데이터 행을 행렬에 추가
            }
        }

        infile.close(); // 파일 닫기

        // 클래스 멤버 변수에 데이터 할당
        rnames = rnms; // 행 이름 할당
        cnames = cnms; // 열 이름 할당

        std::cout << "File read completed: " << filename << std::endl; // 작업 완료 메시지 출력
    }

    void writeTabfile(std::string filename) {
        names cnms, rnms; // 열 이름과 행 이름을 저장하는 벡터

        // 열 이름 설정
        if (cnames.size() == 0) {
            cnms = autonames(ncol(), "C"); // 자동으로 열 이름 생성
        } else {
            cnms = cnames; // 이미 설정된 열 이름 사용
        }

        // 행 이름 설정
        if (rnames.size() == 0) {
            rnms = autonames(nrow(), "R"); // 자동으로 행 이름 생성
        } else {
            rnms = rnames; // 이미 설정된 행 이름 사용
        }

        // 파일을 쓰기 모드로 열기
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // 첫 줄에 열 이름 쓰기
        outfile << "RowNames";
        for (auto c : cnms) {
            outfile << "\t" << c;
        }
        outfile << "\n";

        // 데이터 쓰기
        for (size_t i = 0; i < mt.size(); ++i) {
            outfile << rnms[i]; // 행 이름 쓰기
            for (auto val : mt[i]) {
                outfile << "\t" << val; // 각 행의 데이터 쓰기
            }
            outfile << "\n";
        }

        outfile.close(); // 파일 닫기

        std::cout << "File written: " << filename << std::endl; // 파일 쓰기 완료 메시지 출력
    }

private:
    // 예시로 구현된 autonames 함수
    names autonames(size_t size, std::string prefix) {
        names result;
        for (size_t i = 0; i < size; ++i) {
            result.push_back(prefix + std::to_string(i + 1));
        }
        return result;
    }

    // 예시로 구현된 ncol 함수
    size_t ncol() const {
        if (mt.empty()) return 0;
        return mt[0].size();
    }

    // 예시로 구현된 nrow 함수
    size_t nrow() const {
        return mt.size();
    }
};
